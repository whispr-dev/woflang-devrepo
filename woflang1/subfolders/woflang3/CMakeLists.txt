cmake_minimum_required(VERSION 3.16)
project(woflang CXX)
set(WOFLANG_VERSION "3.0.0")


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(plugins)
add_subdirectory(tests)


# if not then "The source directory .../woflang2/src does not contain a CMakeLists.txt file."
