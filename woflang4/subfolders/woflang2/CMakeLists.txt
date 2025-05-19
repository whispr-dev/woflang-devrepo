cmake_minimum_required(VERSION 3.14)
project(woflang)

set(CMAKE_CXX_STANDARD 17)

add_executable(woflang
    main.cpp
    wof_interpreter.cpp
    plugin_loader.cpp
    repl_commands.cpp
    repl/wofreplrc_loader.cpp
    repl/repl_keybind_expansion_patch.cpp
    repl/repl_plugin_watch_support.cpp
    repl/wof_keybind_autoload_patch.cpp
    repl/repl_blocks_command.cpp
    repl/repl_block_lookup_command.cpp
    repl/repl_block_tree_viewer.cpp
    repl/repl_units_command.cpp
    repl/repl_egg_command.cpp
    repl/repl_mathdoc_command.cpp
    repl/repl_physdoc_command.cpp
    repl/repl_suggest_command.cpp
    repl/repl_woflsigil_chaos.cpp
    repl/repl_woflsigil_command.cpp
    repl/repl_woflsigil_dream.cpp
    repl/repl_woflsigil_purge.cpp
    repl/repl_woflsigil_variants.cpp
)

target_include_directories(woflang PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/repl
    ${CMAKE_SOURCE_DIR}/core
)

get_target_property(INCLUDE_DIRS woflang INCLUDE_DIRECTORIES)
message(STATUS "Include Directories for woflang: ${INCLUDE_DIRS}")

foreach(header "wof_units.hpp" "blocks_and_units.hpp" "block_tracking_support.hpp" "wof_markov_math_suggestions.hpp")
    if(EXISTS "${CMAKE_SOURCE_DIR}/${header}")
        message(STATUS "Found ${header} in ${CMAKE_SOURCE_DIR}")
    else()
        message(WARNING "${header} not found in ${CMAKE_SOURCE_DIR}")
    endif()
endforeach()

target_compile_definitions(woflang PRIVATE
    _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
    _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
)