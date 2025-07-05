cmake_minimum_required(VERSION 3.16)
project(woflang VERSION 3.0.0 LANGUAGES CXX)

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable warnings
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Platform-specific settings
if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-DWOFLANG_PLATFORM_WINDOWS)
    # Windows needs this for dlls to export symbols
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else()
    add_definitions(-DWOFLANG_PLATFORM_UNIX)
endif()

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# SIMD detection
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-mavx2" COMPILER_SUPPORTS_AVX2)
if(COMPILER_SUPPORTS_AVX2)
    add_compile_options(-mavx2)
    add_definitions(-DWOFLANG_USE_AVX2)
endif()

check_cxx_compiler_flag("-mavx512f" COMPILER_SUPPORTS_AVX512)
if(COMPILER_SUPPORTS_AVX512)
    add_compile_options(-mavx512f)
    add_definitions(-DWOFLANG_USE_AVX512)
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm|aarch64)")
    check_cxx_compiler_flag("-mfpu=neon" COMPILER_SUPPORTS_NEON)
    if(COMPILER_SUPPORTS_NEON)
        add_compile_options(-mfpu=neon)
        add_definitions(-DWOFLANG_USE_NEON)
    endif()
endif()

# Source files for core library
file(GLOB_RECURSE CORE_SOURCES 
    "src/core/*.cpp"
    "src/ops/*.cpp"
    "src/glyph/*.cpp"
    "src/repl/*.cpp"
    "src/simd/*.cpp"
    "src/io/*.cpp"
    "src/math/*.cpp"
)

# Define core library
add_library(woflang_core SHARED ${CORE_SOURCES})
target_include_directories(woflang_core PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ops
    ${CMAKE_CURRENT_SOURCE_DIR}/src/glyph
    ${CMAKE_CURRENT_SOURCE_DIR}/src/repl
    ${CMAKE_CURRENT_SOURCE_DIR}/src/simd
    ${CMAKE_CURRENT_SOURCE_DIR}/src/io
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math
)

# Platform-specific dependencies
if(NOT WIN32)
    # Unix: Need dlopen
    target_link_libraries(woflang_core PUBLIC ${CMAKE_DL_LIBS})
endif()

# Main executable
add_executable(woflang main.cpp)
target_link_libraries(woflang PRIVATE woflang_core)

# Plugin folders
add_subdirectory(plugins)

# Test runner
add_executable(woflang_test_runner src/tests/woflang_test_runner.cpp)
target_link_libraries(woflang_test_runner PRIVATE woflang_core)

# Glyph map generator
add_executable(glyph_map_gen src/glyph/glyph_map_gen.cpp)

# Installation rules
install(TARGETS woflang woflang_core woflang_test_runner
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

# Install header files
install(DIRECTORY src/
        DESTINATION include/woflang
        FILES_MATCHING PATTERN "*.hpp")

# Install plugins
install(DIRECTORY ${CMAKE_BINARY_DIR}/plugins/
        DESTINATION plugins
        FILES_MATCHING PATTERN "*.dll" PATTERN "*.so" PATTERN "*.dylib")

# Create REPL setup script for installation
if(WIN32)
    file(WRITE ${CMAKE_BINARY_DIR}/woflang_repl.bat 
         "@echo off\ncd %~dp0\nbin\\woflang.exe\n")
    install(FILES ${CMAKE_BINARY_DIR}/woflang_repl.bat DESTINATION .)
else()
    file(WRITE ${CMAKE_BINARY_DIR}/woflang_repl.sh 
         "#!/bin/sh\ncd \"$(dirname \"$0\")\"\n./bin/woflang\n")
    install(FILES ${CMAKE_BINARY_DIR}/woflang_repl.sh 
            DESTINATION .
            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
endif()

# Copy test scripts to build directory
file(GLOB TEST_SCRIPTS "tests/*.wof")
foreach(TEST_SCRIPT ${TEST_SCRIPTS})
    get_filename_component(SCRIPT_NAME ${TEST_SCRIPT} NAME)
    configure_file(${TEST_SCRIPT} ${CMAKE_BINARY_DIR}/tests/${SCRIPT_NAME} COPYONLY)
endforeach()

# Configure package for system installation (optional)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/woflang-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file(cmake/woflang-config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/woflang-config.cmake"
    @ONLY
)

install(
    FILES 
        "${CMAKE_CURRENT_BINARY_DIR}/woflang-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/woflang-config-version.cmake"
    DESTINATION lib/cmake/woflang
)

# Create plugins/CMakeLists.txt
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/plugins/CMakeLists.txt "
# Built automatically by main CMakeLists.txt
# Find all plugin source files
file(GLOB_RECURSE PLUGIN_SRCS RELATIVE \${CMAKE_CURRENT_SOURCE_DIR} \"*.cpp\")

# Build each plugin as a shared library
foreach(plugin_src \${PLUGIN_SRCS})
    # Extract plugin name from path
    get_filename_component(plugin_name \${plugin_src} NAME_WE)
    
    # Create shared library
    add_library(\${plugin_name} SHARED \${plugin_src})
    
    # Include core headers
    target_include_directories(\${plugin_name} PRIVATE 
        \${CMAKE_SOURCE_DIR}/src/core
        \${CMAKE_SOURCE_DIR}/src/ops
        \${CMAKE_SOURCE_DIR}/src/glyph
        \${CMAKE_SOURCE_DIR}/src
    )
    
    # Link against core if needed (optional)
    # target_link_libraries(\${plugin_name} PRIVATE woflang_core)
    
    # Set output directory for generated DLLs
    set_target_properties(\${plugin_name} PROPERTIES 
        LIBRARY_OUTPUT_DIRECTORY \${CMAKE_BINARY_DIR}/plugins
        RUNTIME_OUTPUT_DIRECTORY \${CMAKE_BINARY_DIR}/plugins
    )
endforeach()
")

# Create cmake/woflang-config.cmake.in
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/woflang-config.cmake.in "
@PACKAGE_INIT@

include(\"\${CMAKE_CURRENT_LIST_DIR}/woflang-targets.cmake\")
check_required_components(woflang)
")

# Print summary
message(STATUS "Woflang configuration:")
message(STATUS "  Version:      ${PROJECT_VERSION}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
if(COMPILER_SUPPORTS_AVX2)
    message(STATUS "  SIMD:         AVX2 enabled")
elseif(COMPILER_SUPPORTS_AVX512)
    message(STATUS "  SIMD:         AVX512 enabled")
elseif(COMPILER_SUPPORTS_NEON)
    message(STATUS "  SIMD:         NEON enabled")
else()
    message(STATUS "  SIMD:         None detected")
endif()
message(STATUS "  Platform:     ${CMAKE_SYSTEM_NAME}")
message(STATUS "  Build Type:   ${CMAKE_BUILD