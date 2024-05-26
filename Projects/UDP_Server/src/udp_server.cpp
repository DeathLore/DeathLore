#define BOOST_ASIO_HAS_CO_AWAIT
#define BOOST_ASIO_HAS_STD_COROUTINE

#include <boost/asio.hpp>
#include <string>
#include <thread>
#include <iostream>
#include <chrono>


namespace asio = boost::asio;

// MY VARIANT

std::string* get_ip4() {
  static std::string ip4 = "127.0.0.1";

  return &ip4;
}

void change_ip4(std::string new_ip4) {
  *get_ip4() = new_ip4;
}

std::string* get_port() {
  static std::string port = "9999";

  return &port;
}

void change_port(std::string new_port) {
  *get_port() = new_port;
}

// void udp_server_output(std::string& received_data) {
//   time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
//   std::cout << "[" << std::put_time(localtime(&now), "%F %T") << "] Received: " << received_data << std::endl;
// }

// /*asio::awaitable<void>*/void udp_server_read(asio::ip::udp::socket& udp_socket) {
//   std::string received_data;
//   received_data.reserve(1500 + 1);
//   std::cout << "1.1" << std::endl;

//   udp_socket.async_receive(asio::buffer(received_data, 1500),
//     [&received_data](boost::system::error_code ec, std::size_t length) {
//       std::cout << "1.2" << std::endl;
//       if (ec) {
//         std::cerr << ec.message() << ec.what() << std::endl;
//         std::cout << "1.3" << std::endl;
//         return;
//       }

//       received_data.back() = '\0';
//       std::cout << "1.3" << std::endl;

//       if (strcmp(received_data.c_str(), "\n") == 0) {
//         return;
//       }
//       std::cout << "1.4" << std::endl;

//       udp_server_output(received_data);
//     }
//   );

//   // co_await udp_server_output(received_data);
// }

// /*asio::awaitable<void>*/void listen_clients(asio::io_context& io_content) {
// //   const auto executor = co_await asio::this_coro::executor;
  

//   asio::ip::udp::endpoint servers_endpoint(asio::ip::udp::v4(), 9997/*atoi(get_port()->c_str())*/); // also listens on ipv4
//   servers_endpoint.address(asio::ip::make_address_v4("127.0.0.1"/*get_ip4()*/));

// //   std::cout << "Ip4: " << *get_ip4() << " Port: " << atoi(get_port()->c_str()) << std::endl;
//   asio::ip::udp::socket udp_socket(/*executor*/io_content, servers_endpoint);
  
  
// //   asio::ip::udp::resolver udp_resolver(executor);  

//   // for (;;) {
//     /*co_await*/ udp_server_read(udp_socket);
//   // }
// }

struct UdpServer {
  explicit UdpServer(asio::ip::udp::socket socket)
    : udp_server_socket(std::move(socket)) { }

  void server_receive_data() {
    udp_server_socket.async_receive(asio::buffer(received_data, 1500),
      [this](boost::system::error_code ec, std::size_t length) {

        if (ec) {
          std::cerr << ec.message() << ec.what() << std::endl;
          return;
        }

        received_data[length] = '\0';

        if (strcmp(received_data, "\n") == 0) {
          return;
        }

        this->redirect_data_in_cout();
      }
    );
  }
private:
  void redirect_data_in_cout() {
    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "[" << std::put_time(localtime(&now), "%F %T") << "] Received: " << received_data << std::endl;
  }

  asio::ip::udp::socket udp_server_socket;
  asio::ip::udp::endpoint server_endpoint;
  char received_data[1500 + 1];
};

void runUDPServer() {
  asio::io_context ioContext;

  asio::ip::udp::endpoint server_endpoint(asio::ip::udp::v4(), atoi(get_port()->c_str()));
  server_endpoint.address(asio::ip::make_address_v4(*get_ip4()));

  asio::ip::udp::socket udp_socket(ioContext, server_endpoint);

  UdpServer LocalUDPServer(std::move(udp_socket));

  // bool receiving = false;

  LocalUDPServer.server_receive_data();
  
  // /*asio::co_spawn(ioContext, */listen_clients(ioContext)/*, asio::detached)*/;

  ioContext.run();

}


int main(int argc, char **argv) {
  char exit_status = EXIT_SUCCESS;
  try {
    if (argc != 3)
      throw std::domain_error("Usage: udp_server <address> <port>");

    change_ip4(argv[1]);
    change_port(argv[2]);

    runUDPServer();
  } catch (const std::exception& ex) {
    exit_status = EXIT_FAILURE;

    std::cerr << ex.what() << std::endl;
  }

  return (int)exit_status;
}
