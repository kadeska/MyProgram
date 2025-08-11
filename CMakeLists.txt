cmake_minimum_required(VERSION 3.10)

project(MyProgram VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify include directories
include_directories(${CMAKE_SOURCE_DIR}/src/include)
include_directories(${CMAKE_SOURCE_DIR}/external/asio)

# Add the executable and source files
add_executable(MyProgram 
    src/main.cpp
    src/helper.cpp
    src/IOmanager.cpp
    src/commands.cpp
)

# Define ASIO_STANDALONE for the compiler
target_compile_definitions(MyProgram PRIVATE ASIO_STANDALONE)

# Link with ws2_32 for Windows sockets support
if (WIN32)
    target_link_libraries(MyProgram PRIVATE ws2_32)
endif()
