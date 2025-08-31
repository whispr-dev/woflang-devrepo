cmake_minimum_required(VERSION 3.20)

project(woflang
  VERSION 3.0.0
  LANGUAGES CXX)

# --- language / warnings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --- output dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

# plugins (DLL) go here:
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}/bin/plugins)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/bin/plugins)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/plugins)

# import libs / static libs here:
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}/lib)

# --- includes available to core + plugins
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/core
  ${CMAKE_CURRENT_SOURCE_DIR}/plugins
)

# --- find main (prefer these paths, else fail)
set(WOFLANG_MAIN "")
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/repl/main.cpp")
  set(WOFLANG_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/src/repl/main.cpp")
elseif (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
  set(WOFLANG_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
elseif (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
  set(WOFLANG_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
endif()

if (WOFLANG_MAIN STREQUAL "")
  message(FATAL_ERROR "Cannot find main.cpp. Expected one of: src/repl/main.cpp, src/main.cpp, or ./main.cpp")
endif()

# --- collect core sources from src/** (but exclude main and anything inside plugins/tests)
file(GLOB_RECURSE ALL_SRC_CPP CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*.cpp
)

# exclude main
list(REMOVE_ITEM ALL_SRC_CPP "${WOFLANG_MAIN}")

# exclude anything under plugins/ or tests/
set(WOFLANG_CORE_SRC "")
foreach(SRC ${ALL_SRC_CPP})
  if (SRC MATCHES "/plugins/" OR SRC MATCHES "/tests/")
    # skip
  else()
    list(APPEND WOFLANG_CORE_SRC "${SRC}")
  endif()
endforeach()

if (WOFLANG_CORE_SRC STREQUAL "")
  message(FATAL_ERROR "No core sources found under src/**. Did you move files?")
endif()

# --- core lib
add_library(woflang_core STATIC ${WOFLANG_CORE_SRC})
target_compile_definitions(woflang_core PRIVATE WOFLANG_BUILDING_CORE)

# --- exe
add_executable(woflang ${WOFLANG_MAIN})
target_link_libraries(woflang PRIVATE woflang_core)
set_target_properties(woflang PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)

# --- plugins subdir
add_subdirectory(plugins)
