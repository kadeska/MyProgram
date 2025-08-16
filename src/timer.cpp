#include "include/timer.hpp"



int foo_sync() {
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(5));
    t.wait();
    std::cout << "Hello, world!" << std::endl;
    return 0;
}

int foo_async() {
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(5));
    t.async_wait(&print);
    io.run();
    return 0;
}

void print(const std::error_code& /*e*/)
{
  std::cout << "Hello, world!" << std::endl;
}