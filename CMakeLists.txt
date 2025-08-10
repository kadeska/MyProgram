cmake_minimum_required(VERSION 3.10) # Specifies the minimum required CMake version

project(MyProgram VERSION 1.0)  # Set project name and version

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 23)

# Specify the include directory for header files
include_directories(${CMAKE_SOURCE_DIR}/src/include)

# Add executable target with the source files
add_executable(MyProgram 
    src/main.cpp
    src/helper.cpp
    src/IOmanager.cpp
    src/commands.cpp
)
