#pragma once

#include <iostream>
#include <string>
#include <asio.hpp>

// Define server details
const std::string SERVER_HOST = "127.0.0.1";
const std::string CLIENT_PORT = "13";

class TcpClient {
public:
    TcpClient(asio::io_context& io_context, const std::string& host, const std::string& port);
    void run();
    void run(std::string msg);
    bool proccessData(std::string data);

private:
    asio::io_context& io_context_;
    std::string host_;
    std::string port_;
};