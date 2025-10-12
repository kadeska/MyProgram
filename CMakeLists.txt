cmake_minimum_required(VERSION 3.24)
project(MyProgram VERSION 0.1.0)

# Add the SDL subdirectories and build them with your project.
add_subdirectory(external/SDL)
# add_subdirectory(external/SDL_image)


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
   # src/window.cpp
 "src/mapGenerator.cpp" "src/entityGenerator.cpp")

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

# Link your executable to the SDL3 and SDL3_image libraries.
target_link_libraries(MyProgram PRIVATE
    ws2_32
    mswsock
    SDL3::SDL3
    # SDL3_image::SDL3_image  # Add the SDL3_image library
)

# Use the TARGET_FILE generator expression to get the path reliably.
if (WIN32)
    add_custom_command(TARGET MyProgram POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3::SDL3>"
            "$<TARGET_FILE_DIR:MyProgram>"
    )
    # Copy the SDL3_image DLL as well.
   # add_custom_command(TARGET MyProgram POST_BUILD
   #     COMMAND ${CMAKE_COMMAND} -E copy_if_different
   #         "$<TARGET_FILE:SDL3_image::SDL3_image>"
   #         "$<TARGET_FILE_DIR:MyProgram>"
   # )
endif()