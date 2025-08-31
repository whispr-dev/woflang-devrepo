cmake_minimum_required(VERSION 3.16)
project(woflang VERSION 3.0.0 LANGUAGES C CXX)

cmake_minimum_required(VERSION 3.16)
project(woflang VERSION 3.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# core (header-only fallback)
file(GLOB_RECURSE CORE_SOURCES "${CMAKE_SOURCE_DIR}/src/**/*.cpp" "${CMAKE_SOURCE_DIR}/core/*.cpp")
if(CORE_SOURCES)
  add_library(woflang_core STATIC ${CORE_SOURCES})
else()
  add_library(woflang_core INTERFACE)
endif()
target_include_directories(woflang_core PUBLIC
  ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/core ${CMAKE_SOURCE_DIR}/plugins)

add_executable(woflang ${CMAKE_SOURCE_DIR}/main.cpp) # change if yours is main_interpreter.cpp
target_link_libraries(woflang PRIVATE woflang_core)

add_subdirectory(plugins)

message(STATUS "Woflang configuration:")
message(STATUS "  Version:      ${PROJECT_VERSION}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  EXE dir:      ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
