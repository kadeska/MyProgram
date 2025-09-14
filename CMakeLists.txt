cmake_minimum_required(VERSION 3.24)
project(MyProgram VERSION 1.0)

# Add the SDL subdirectory and build it with your project.
add_subdirectory(external/SDL)

add_executable(MyProgram
    src/main.cpp
    src/helper.cpp
    src/IOmanager.cpp
    src/commands.cpp
    src/client.cpp
    src/server.cpp
    src/timer.cpp
    src/networkManager.cpp
    src/inputManager.cpp
    src/window.cpp
)

set_property(TARGET MyProgram PROPERTY CXX_STANDARD 23)
set_property(TARGET MyProgram PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(MyProgram PRIVATE
    src/include
    external/asio
)

target_compile_definitions(MyProgram PRIVATE
    _WIN32_WINNT=0x0A00
    ASIO_STANDALONE
)

# Link your executable to the SDL3 library.
target_link_libraries(MyProgram PRIVATE
    ws2_32
    mswsock
    SDL3::SDL3
)

# Use the TARGET_FILE generator expression to get the path reliably.
if (WIN32)
    add_custom_command(TARGET MyProgram POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3::SDL3>"
            "$<TARGET_FILE_DIR:MyProgram>"
    )
endif()