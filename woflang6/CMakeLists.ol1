cmake_minimum_required(VERSION 3.16)
project(woflang VERSION 3.0.0 LANGUAGES CXX)

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Create plugins directory in build folder
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/plugins)

# Platform detection
if(WIN32)
    add_definitions(-DWOFLANG_PLATFORM_WINDOWS)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# Compiler settings
if(MSVC)
    add_compile_options(/W4 /permissive- /utf-8)
    # Force MSVC to use latest C++ features
    add_compile_options(/std:c++latest)
endif()

# Core library
add_library(woflang_core STATIC
    src/core/woflang.cpp
    src/io/tokenizer.cpp
)

target_include_directories(woflang_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Main executable - using the file in src/repl
add_executable(woflang
    src/repl/repl_main.cpp
)

target_link_libraries(woflang PRIVATE woflang_core)

# Plugin building function
function(add_woflang_plugin name source)
    add_library(${name} SHARED ${source})
    
    target_include_directories(${name} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
    
    # Set output directory
    set_target_properties(${name} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/plugins"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/plugins"
    )
    
    # Windows-specific: ensure .dll extension
    if(WIN32)
        set_target_properties(${name} PROPERTIES
            SUFFIX ".dll"
        )
    endif()
endfunction()

# Build plugins (check if they exist first)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/plugins/math_ops.cpp)
    add_woflang_plugin(math_ops plugins/math_ops.cpp)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/plugins/math_greek.cpp)
    add_woflang_plugin(math_greek plugins/math_greek.cpp)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/plugins/logic_ops.cpp)
    add_woflang_plugin(logic_ops plugins/logic_ops.cpp)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/plugins/crypto_ops.cpp)
    add_woflang_plugin(crypto_ops plugins/crypto_ops.cpp)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/plugins/fractal_ops.cpp)
    add_woflang_plugin(fractal_ops plugins/fractal_ops.cpp)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/plugins/quantum_ops.cpp)
    add_woflang_plugin(quantum_ops plugins/quantum_ops.cpp)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/plugins/chemistry_ops.cpp)
    add_woflang_plugin(chemistry_ops plugins/chemistry_ops.cpp)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/plugins/kanji_ops.cpp)
    add_woflang_plugin(kanji_ops plugins/kanji_ops.cpp)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/plugins/music_ops.cpp)
    add_woflang_plugin(music_ops plugins/music_ops.cpp)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/plugins/entropy_op.cpp)
    add_woflang_plugin(entropy_op plugins/entropy_op.cpp)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/plugins/prophecy_op.cpp)
    add_woflang_plugin(prophecy_op plugins/prophecy_op.cpp)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/plugins/stack_slayer_op.cpp)
    add_woflang_plugin(stack_slayer_op plugins/stack_slayer_op.cpp)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/plugins/void_division_op.cpp)
    add_woflang_plugin(void_division_op plugins/void_division_op.cpp)
endif()

# Summary
message(STATUS "")
message(STATUS "Woflang Configuration Summary:")
message(STATUS "  Version:       ${PROJECT_VERSION}")
message(STATUS "  C++ Standard:  ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type:    ${CMAKE_BUILD_TYPE}")
message(STATUS "  Platform:      ${CMAKE_SYSTEM_NAME}")
message(STATUS "  Compiler:      ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "")