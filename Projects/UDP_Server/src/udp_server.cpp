#define BOOST_ASIO_HAS_CO_AWAIT
#define BOOST_ASIO_HAS_STD_COROUTINE

#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <string>

#define REC_DATA_SIZE (1500 + 1)

namespace asio = boost::asio;

std::string* get_ip4() {
  static std::string ip4 = "127.0.0.1";

  return &ip4;
}

void change_ip4(std::string new_ip4) { *get_ip4() = new_ip4; }

std::string* get_port() {
  static std::string port = "9999";

  return &port;
}

void change_port(std::string new_port) { *get_port() = new_port; }

struct UdpServer {
  explicit UdpServer(asio::ip::udp::socket socket)
      : udp_server_socket(std::move(socket)) {}

  asio::awaitable<void> server_receive_data() {
    asio::ip::udp::endpoint connected_endpoint;

    udp_server_socket.async_receive_from(
        asio::buffer(received_data, REC_DATA_SIZE - 1), connected_endpoint,
        std::bind(&UdpServer::redirect_data_in_cout, this,
                  std::placeholders::_1, std::placeholders::_2));

    co_return;
  }

  asio::io_context server_ioContext;

 private:
  void redirect_data_in_cout(boost::system::error_code error_code,
                             std::size_t length) {
    if (error_code) {
      std::cerr << error_code.message() << "\n"
                << error_code.what() << std::endl;
      return;
    }
    received_data[length] = '\0';

    if (strcmp(received_data, "\n") == 0) {
      return;
    }

    // Getting current time
    time_t now =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "[" << std::put_time(localtime(&now), "%F %T")
              << "] Received: " << received_data << std::endl;

    // Flushing received_data after use
    memset(received_data, 0, REC_DATA_SIZE);
  }

  asio::ip::udp::socket udp_server_socket;
  asio::ip::udp::endpoint server_endpoint;
  char received_data[REC_DATA_SIZE];
};

asio::awaitable<void> start_listen(asio::ip::udp::endpoint& server_endpoint,
                                   asio::io_context& ioContext) {
  // const auto executor = co_await asio::this_coro::executor;

  // Getting current context
  asio::io_context listening_context;

  // Making servers socket
  asio::ip::udp::socket udp_socket(listening_context, server_endpoint);
  UdpServer LocalUDPServer(std::move(udp_socket));

  asio::co_spawn(listening_context, LocalUDPServer.server_receive_data(),
                 asio::detached);
  listening_context.run();  // Forcing async_receive to use handler

  co_return;
}

asio::awaitable<void> runUDPServer(asio::io_context& ioContext) {
  // Getting coroutine's context
  const auto executor = co_await asio::this_coro::executor;

  // Setting up UDP server's IPv4 address and port
  asio::ip::udp::endpoint server_endpoint(asio::ip::udp::v4(),
                                          atoi(get_port()->c_str()));
  server_endpoint.address(asio::ip::make_address_v4(*get_ip4()));

  for (;;) {
    // Spawning coroutines for receiving data
    asio::co_spawn(executor, start_listen(server_endpoint, ioContext),
                   asio::detached);
  }

  co_return;
}

int main(int argc, char** argv) {
  char exit_status = EXIT_SUCCESS;
  try {
    // Checks if address and port were inserted
    if (argc != 3)
      throw std::domain_error("Usage: udp_server <address> <port>");

    if (atoi(argv[1]) <= 0) throw std::domain_error("Wrong server's port.");

    change_port(argv[2]);
    change_ip4(argv[1]);
    boost::system::error_code er_code;
    // Validating inserted IPv4 address
    asio::ip::address::from_string(*get_ip4(), er_code);
    if (er_code) throw std::domain_error("Invalid IPv4 address!");

    asio::io_context ioContext;

    // Spawning main coroutine
    asio::co_spawn(ioContext, runUDPServer(ioContext), asio::detached);

    ioContext.run();
  } catch (const std::exception& ex) {
    exit_status = EXIT_FAILURE;

    std::cerr << ex.what() << std::endl;
  }

  return (int)exit_status;
}