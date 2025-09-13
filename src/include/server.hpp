#pragma once

#include <iostream>
#include <string>
#include <asio.hpp>

#include "helper.hpp"

// Define port for communication
const std::string SERVER_PORT = "13";

class TcpServer {
public:
    TcpServer(asio::io_context& io_context, Helper mHelper);
    void run();
    std::string generateRandInt(int seed);
    // std::string generate

private:
    Helper helper;
    void handle_client(asio::ip::tcp::socket& socket);
    asio::io_context& io_context_;
    asio::ip::tcp::acceptor acceptor_;
};