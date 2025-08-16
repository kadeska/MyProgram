#pragma once
#include <iostream>
#include <asio.hpp>

void print(const std::error_code& /*e*/);
int foo_sync();
int foo_async();