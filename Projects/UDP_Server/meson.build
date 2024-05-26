project('udp_server', 'cpp',
  version: '0.1',
  default_options: ['cpp_std=c++20'])

asio_dep = subproject('asio').get_variable('asio_dep')

executable('udp_server', 'src/udp_server.cpp',
  dependencies: asio_dep)