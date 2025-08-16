#include "include/client.hpp"


using asio::ip::tcp;

int client(int argc, char const *argv[], Helper helper) {
    try
    {
        if (argc != 2) {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }
        asio::io_context io_context;
        tcp::resolver resolver(io_context);
        // tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "daytime");
        tcp::resolver::results_type endpoints = resolver.resolve("localhost", "daytime");
        tcp::socket socket(io_context);
        asio::connect(socket, endpoints);
        
        for (;;)
        {
            std::array<char, 128> buf;
            std::error_code error;
            size_t len = socket.read_some(asio::buffer(buf), error);
            if (error == asio::error::eof)
            break; // Connection closed cleanly by peer.
            else if (error)
            throw std::system_error(error); // Some other error.
            std::string str(buf.data()); // = buf.data();
            // std::cout.write(buf.data(), len);
            helper.logInfo(str);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;

}