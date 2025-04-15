cmake_minimum_required(VERSION 3.16)
project(woflang)

set(CMAKE_CXX_STANDARD 20)

include_directories(core simd parser repl ops io)

file(GLOB_RECURSE SOURCES
     "core/*.cpp"
     "parser/*.cpp"
     "repl/*.cpp"
     "ops/*.cpp"
     "io/*.cpp")

add_executable(woflang ${SOURCES})
