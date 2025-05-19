cmake_minimum_required(VERSION 3.16)
project(woflang VERSION 3.0.0 LANGUAGES CXX)

# C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(PLUGIN_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins)

# Make sure include paths are properly set
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Define platform
if(WIN32)
    add_definitions(-DWOFLANG_PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
    add_definitions(-DWOFLANG_PLATFORM_LINUX)
elseif(APPLE)
    add_definitions(-DWOFLANG_PLATFORM_MACOS)
endif()

# Create a simple application for testing the core
add_executable(woflang src/repl/repl_main.cpp)

# Add the tokenizer
target_sources(woflang PRIVATE src/io/tokenizer.cpp)

message(STATUS "Woflang configuration:")
message(STATUS "  Version:      ${PROJECT_VERSION}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Platform:     ${CMAKE_SYSTEM_NAME}")
message(STATUS "  Build Type:   ${CMAKE_BUILD_TYPE}")

# Add this near the top of your CMakeLists.txt, after your project() statement
# This tells the compiler to look in these directories for header files
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/repl
    ${CMAKE_CURRENT_SOURCE_DIR}/src/io
)