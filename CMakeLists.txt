cmake_minimum_required(VERSION 3.24)
project(MyProgram VERSION 0.1.1)

# If building on Windows with MinGW (GNU), prefer building static libraries.
if(WIN32 AND CMAKE_C_COMPILER_ID STREQUAL "GNU")
    message(STATUS "MinGW detected on Windows: forcing static libraries (BUILD_SHARED_LIBS=OFF)")
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
endif()

# Set output directories for binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

foreach(OUTPUTCONFIG IN ITEMS Debug Release RelWithDebInfo MinSizeRel)
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UP)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UP} ${CMAKE_BINARY_DIR}/bin/${OUTPUTCONFIG})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UP} ${CMAKE_BINARY_DIR}/lib/${OUTPUTCONFIG})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UP} ${CMAKE_BINARY_DIR}/bin/${OUTPUTCONFIG})
endforeach()

# Add executable
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
    src/mapGenerator.cpp
    src/entityGenerator.cpp
    src/entityManager.cpp
    src/game.cpp
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
    $<$<CONFIG:Release>:NDEBUG>
    $<$<CONFIG:Debug>:_DEBUG>
)

target_compile_options(MyProgram PRIVATE
    $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2 /GL>
    $<$<AND:$<CONFIG:Release>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-O3 -flto>
    $<$<AND:$<CONFIG:RelWithDebInfo>,$<CXX_COMPILER_ID:MSVC>>:/O2 /Zi>
    $<$<AND:$<CONFIG:RelWithDebInfo>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-O2 -g>
)

target_link_options(MyProgram PRIVATE
    $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/LTCG>
    $<$<AND:$<CONFIG:Release>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-flto>
)

# Link libraries (removed SDL)
target_link_libraries(MyProgram PRIVATE
    ws2_32
    mswsock
)

# Copy runtime data folder only if the source exists to avoid failing the build.
if (EXISTS "${CMAKE_SOURCE_DIR}/data" AND IS_DIRECTORY "${CMAKE_SOURCE_DIR}/data")
    add_custom_command(TARGET MyProgram POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/data"
            "$<TARGET_FILE_DIR:MyProgram>/data"
    )
else()
    message(WARNING "Project data directory '${CMAKE_SOURCE_DIR}/data' not found; skipping copy of runtime data.")
endif()

option(ENABLE_LTO "Enable link time optimization where supported" ON)
if(ENABLE_LTO)
    message(STATUS "Link-time optimization enabled where supported")
endif()

# Print status messages for debugging
message(STATUS "CMake version: ${CMAKE_VERSION}")
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
