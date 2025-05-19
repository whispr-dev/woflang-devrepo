cmake_minimum_required(VERSION 3.14)
project(wofvalue_explorer)

set(CMAKE_CXX_STANDARD 17)

# Simple CMakeLists.txt for exploring WofValue
add_executable(wofvalue_explorer
    wofvalue_explorer.cpp
    wof_interpreter.cpp  # Include the interpreter source
)

# Include project root directory and subdirectories
target_include_directories(wofvalue_explorer PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/repl
    ${CMAKE_SOURCE_DIR}/core
)