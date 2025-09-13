cmake_minimum_required(VERSION 3.24)
project(MyProgram VERSION 1.0)

# add_subdirectory(MyProgram)


# Add the executable and source files first. This creates the 'MyProgram' target.
add_executable(MyProgram
    src/main.cpp
    src/helper.cpp
    src/IOmanager.cpp
    src/commands.cpp
    src/client.cpp
    src/server.cpp
    src/timer.cpp
    src/networkManager.cpp
)

# Now set properties on the target, since it now exists.
set_property(TARGET MyProgram PROPERTY CXX_STANDARD 23)
set_property(TARGET MyProgram PROPERTY CXX_STANDARD_REQUIRED ON)

# Specify include directories for the target using a target-specific command.
target_include_directories(MyProgram PRIVATE
    src/include
    external/asio
)

# Add compile definitions to the target. Use the "target_compile_definitions" command.
# The definitions are private to the target's compilation.
target_compile_definitions(MyProgram PRIVATE
    _WIN32_WINNT=0x0A00
    ASIO_STANDALONE
)

# Link with required libraries. These links are also private to the target.
if (WIN32)
    target_link_libraries(MyProgram PRIVATE
        ws2_32
        mswsock
    )
endif()

