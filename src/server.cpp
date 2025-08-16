#include "include/server.hpp"

using asio::ip::tcp;

int server() {
    try 
    {
        asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13)); 
        for (;;)
        {
            std::cout << "Listening for connection..." << std::endl;
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::string message = make_daytime_string();
            std::error_code ignored_error;
            asio::write(socket, asio::buffer(message), ignored_error);
            std::cout << "Connection made, sent message: " << message << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}