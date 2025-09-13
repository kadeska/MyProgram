#include "include/client.hpp"
#include <chrono>

using asio::ip::tcp;

TcpClient::TcpClient(asio::io_context& io_context, const std::string& host, const std::string& port)
    : io_context_(io_context),
      host_(host),
      port_(port) {}

void TcpClient::run() {
    try {
        tcp::resolver resolver(io_context_);
        tcp::resolver::results_type endpoints = resolver.resolve(host_, port_);

        tcp::socket socket(io_context_);
        asio::connect(socket, endpoints);

        // Send a request to the server
        std::string client_message = "Client: Asking for data.\n";
        asio::write(socket, asio::buffer(client_message));

        // Read the server's response
        asio::error_code error;
        asio::streambuf response_buf;
        asio::read_until(socket, response_buf, '\n', error);
        
        if (error && error != asio::error::eof) {
            throw asio::system_error(error);
        }

        std::istream response_stream(&response_buf);
        std::string response_message;
        std::getline(response_stream, response_message);
        std::cout << "Received from server: " << response_message << std::endl;

    } catch (std::exception& e) {
        std::cerr << "Client exception: " << e.what() << std::endl;
    }
}

void TcpClient::run(std::string msg) {
    try {
        tcp::resolver resolver(io_context_);
        tcp::resolver::results_type endpoints = resolver.resolve(host_, port_);

        tcp::socket socket(io_context_);
        asio::connect(socket, endpoints);

        // Send a request to the server
        // std::string client_message = "Client: Asking for data.\n";
        asio::write(socket, asio::buffer(msg));

        // Read the server's response
        asio::error_code error;
        asio::streambuf response_buf;
        asio::read_until(socket, response_buf, '\n', error);
        
        if (error && error != asio::error::eof) {
            throw asio::system_error(error);
        }

        std::istream response_stream(&response_buf);
        std::string response_message;
        std::getline(response_stream, response_message);
        std::cout << "Received from server: " << response_message << std::endl;
        //if (proccessData(response_message)) {}
        

    } catch (std::exception& e) {
        std::cerr << "Client exception: " << e.what() << std::endl;
    }
}

bool TcpClient::proccessData(std::string data) {return true;}

int TcpClient::waitForInput(Helper helper)
{
    std::cout << "testing" << std::endl;
    try {
        helper.logInfo("waiting");
        if (waitLoop == false) {
            waitLoop = true;
            helper.logInfo("Entering wait loop. Type 'exit' to quit.");
        }
        while (waitLoop) {
            helper.logInfo("Please enter something > ");
            std::string entry;
            std::getline(std::cin, entry);
            helper.logInfo("You entered: " + entry);
        }
    } catch (std::exception& e) {
        std::cerr << "Client exception: " << e.what() << std::endl;
	}
    
    
    return 0;
}