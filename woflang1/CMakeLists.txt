cmake_minimum_required(VERSION 3.14)
project(woflang)

set(CMAKE_CXX_STANDARD 17)

add_executable(woflang
    main.cpp
    wof_interpreter.cpp
    plugin_loader.cpp
    repl_commands.cpp
)

# include dirs if needed
target_include_directories(woflang PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# for dynamic loading
target_link_libraries(woflang dl)
