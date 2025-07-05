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
elseif(APPLE)
    add_definitions(-DWOFLANG_PLATFORM_MACOS)
else()
    add_definitions(-DWOFLANG_PLATFORM_LINUX)
endif()

# Compiler warnings
if(MSVC)
    add_compile_options(/W4 /permissive- /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Check for SIMD support
include(CheckCXXCompilerFlag)
if(NOT MSVC)
    check_cxx_compiler_flag("-mavx2" COMPILER_SUPPORTS_AVX2)
    if(COMPILER_SUPPORTS_AVX2)
        add_compile_options(-mavx2)
        add_definitions(-DWOFLANG_HAS_AVX2)
    endif()
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

# Link with platform-specific libraries
if(NOT WIN32)
    target_link_libraries(woflang_core PUBLIC dl)
endif()

# Main executable
add_executable(woflang
    src/repl/repl_main.cpp
)

target_link_libraries(woflang PRIVATE woflang_core)

# Install rules
install(TARGETS woflang
    RUNTIME DESTINATION bin
)

install(DIRECTORY ${CMAKE_BINARY_DIR}/bin/plugins
    DESTINATION bin
)

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
    
    # Platform-specific settings
    if(APPLE)
        set_target_properties(${name} PROPERTIES
            SUFFIX ".dylib"
        )
    endif()
    
    # Install plugin
    install(TARGETS ${name}
        LIBRARY DESTINATION bin/plugins
        RUNTIME DESTINATION bin/plugins
    )
endfunction()

# Build plugins
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/plugins)
    # Core plugins
    add_woflang_plugin(math_ops plugins/math_ops.cpp)
    add_woflang_plugin(math_greek plugins/math_greek.cpp)
    add_woflang_plugin(logic_ops plugins/logic_ops.cpp)
    add_woflang_plugin(crypto_ops plugins/crypto_ops.cpp)
    add_woflang_plugin(fractal_ops plugins/fractal_ops.cpp)
    add_woflang_plugin(quantum_ops plugins/quantum_ops.cpp)
    add_woflang_plugin(music_ops plugins/music_ops.cpp)
    add_woflang_plugin(chemistry_ops plugins/chemistry_ops.cpp)
    add_woflang_plugin(kanji_ops plugins/kanji_ops.cpp)
    
    # Sacred/special plugins
    add_woflang_plugin(entropy_op plugins/entropy_op.cpp)
    add_woflang_plugin(prophecy_op plugins/prophecy_op.cpp)
    add_woflang_plugin(stack_slayer_op plugins/stack_slayer_op.cpp)
    add_woflang_plugin(void_division_op plugins/void_division_op.cpp)
endif()

# Tests
enable_testing()

# Test runner
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/tests/woflang_test_runner.cpp)
    add_executable(woflang_test src/tests/woflang_test_runner.cpp)
    target_link_libraries(woflang_test PRIVATE woflang_core)
    
    # Copy test scripts
    file(GLOB TEST_SCRIPTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.wof")
    foreach(script ${TEST_SCRIPTS})
        get_filename_component(script_name ${script} NAME)
        configure_file(${script} ${CMAKE_BINARY_DIR}/tests/${script_name} COPYONLY)
    endforeach()
    
    add_test(NAME WoflangTests COMMAND woflang_test)
endif()

# Package configuration
include(GNUInstallDirs)

# Create version file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/woflang-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Configure file
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/woflang-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/woflang-config.cmake"
    @ONLY
)

# Install config files
install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/woflang-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/woflang-config-version.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/woflang
)

# Summary
message(STATUS "")
message(STATUS "Woflang Configuration Summary:")
message(STATUS "  Version:       ${PROJECT_VERSION}")
message(STATUS "  C++ Standard:  ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type:    ${CMAKE_BUILD_TYPE}")
message(STATUS "  Platform:      ${CMAKE_SYSTEM_NAME}")
message(STATUS "  Install Path:  ${CMAKE_INSTALL_PREFIX}")
if(COMPILER_SUPPORTS_AVX2)
    message(STATUS "  SIMD Support:  AVX2 enabled")
else()
    message(STATUS "  SIMD Support:  Disabled")
endif()
message(STATUS "")