#include "include/server.hpp"
#include "server.hpp"
#include <random>
using asio::ip::tcp;

TcpServer::TcpServer(asio::io_context& io_context, Helper mHelper)
    : io_context_(io_context),
      acceptor_(io_context, tcp::endpoint(tcp::v4(), std::stoi(SERVER_PORT))) {helper = mHelper;}

void TcpServer::run() {
    try {
        // std::cout << "Server is listening on port " << SERVER_PORT << std::endl;
        helper.log("Server is listening on port " + SERVER_PORT);
        for (;;) {
            tcp::socket socket(io_context_);
            acceptor_.accept(socket);
            handle_client(socket);
            std::cout << "Connection closed. Waiting for a new client..." << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Server exception: " << e.what() << std::endl;
    }
}

std::string TcpServer::generateData(int seed)
{
    // 1. Obtain a random device for seeding
    std::random_device rd;

    // 2. Seed a Mersenne Twister engine
    std::mt19937 gen(rd() + seed);

    // 3. Define a uniform integer distribution for the desired range
    //    Here, between 1 and 100 (inclusive)
    std::uniform_int_distribution<> distrib(1, 100);

    // 4. Generate and print a random number
    int randomNumber = distrib(gen);
    std::cout << "Random number: " << randomNumber << std::endl;

    return std::to_string(randomNumber);
}

void TcpServer::handle_client(tcp::socket& socket) {
    try {
        // Read until a newline from the client
        asio::error_code error;
        asio::streambuf request_buf;
        asio::read_until(socket, request_buf, '\n', error);

        if (error && error != asio::error::eof) {
            throw asio::system_error(error);
        }

        std::istream request_stream(&request_buf);
        std::string client_message;
        std::getline(request_stream, client_message);
        std::cout << "Received message from client: " << client_message << std::endl;
        // proccess message

        // Send a response back to the client
        std::string response_message = generateData(3); // "123,456,789\n";
        asio::write(socket, asio::buffer(response_message), error);

        if (error) {
            throw asio::system_error(error);
        }
        std::cout << "Sent response to client." << std::endl;

    } catch (std::exception& e) {
        std::cerr << "Exception in client handler: " << e.what() << std::endl;
    }
}

