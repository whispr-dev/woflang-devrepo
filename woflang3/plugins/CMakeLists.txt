file(GLOB PLUGINS_SRC *.cpp)
foreach(plugin_src ${PLUGINS_SRC})
    get_filename_component(plugin_name ${plugin_src} NAME_WE)
    add_library(${plugin_name} SHARED ${plugin_src})
    target_include_directories(${plugin_name} PRIVATE ../src/core)
endforeach()



cmake_minimum_required(VERSION 3.24)
project(math_constants_plugin CXX)

set(CMAKE_CXX_STANDARD 23)
add_library(math_constants SHARED math_constants.cpp)
target_include_directories(math_constants PRIVATE ../../src)

add_library(symbolic_solve SHARED symbolic_solve.cpp)
target_include_directories(symbolic_solve PRIVATE ../../src)

cmake_minimum_required(VERSION 3.24)
project(woflang CXX)

set(CMAKE_CXX_STANDARD 23)
set(SRC
    src/core/woflang.cpp
    src/io/plugin_loader.cpp
    src/ops/core_ops.hpp
    src/repl/repl_commands.hpp
    src/math/symbolic_engine.hpp
    main.cpp
)

add_executable(woflang ${SRC})

# Plugin DLL
add_subdirectory(plugins)

# Test runner
add_executable(woflang_test_runner src/tests/woflang_test_runner.cpp)
target_include_directories(woflang_test_runner PRIVATE src)

# Glyph map CLI
add_executable(glyph_map_gen src/glyph/glyph_map_gen.cpp)

add_executable(plugin_autoloader src/io/plugin_autoloader.cpp)

add_library(markov_suggest SHARED markov_suggest.cpp)
target_include_directories(markov_suggest PRIVATE ../../src)

add_library(math_constants SHARED mathlib_constants.cpp)
target_include_directories(math_constants PRIVATE ../../src)

add_library(mathlib_calculus SHARED mathlib_calculus.cpp)
target_include_directories(mathlib_calculus PRIVATE ../../src)

add_library(mathlib_exponentials SHARED mathlib_exponentials.cpp)
target_include_directories(mathlib_exponentials PRIVATE ../../src)

add_library(physics_constants SHARED load_physics_constants.cpp)
target_include_directories(physics_constants PRIVATE ../../src)

add_library(modelica_constants SHARED load_modelica_constants.cpp)
target_include_directories(modelica_constants PRIVATE ../../src)

add_library(symbolic_simplify_rules SHARED ops_symbolic_simplify_rules.cpp)
target_include_directories(symbolic_simplify_rules PRIVATE ../../src)

add_library(symbolic_solve_linear SHARED ops_symbolic_solve_linear.cpp)
target_include_directories(symbolic_solve_linear PRIVATE ../../src)

add_library(symbolic_solve_patterns SHARED ops_symbolic_solve_patterns.cpp)
target_include_directories(symbolic_solve_patterns PRIVATE ../../src)

add_library(wof_markov_math_suggestions SHARED wof_markov_math_suggestions.cpp)
target_include_directories(wof_markov_math_suggestions PRIVATE ../../src)

add_library(repl_egg_command SHARED repl_egg_command.cpp)
target_include_directories(repl_egg_command PRIVATE ../../src)

add_library(forbidden_stack_slayer SHARED ops_forbidden_stack_slayer.cpp)
target_include_directories(forbidden_stack_slayer PRIVATE ../../src)

add_library(repl_history_commands SHARED repl_history_commands.cpp)
target_include_directories(repl_history_commands PRIVATE ../../src)

add_library(repl_suggest_command SHARED repl_suggest_command.cpp)
target_include_directories(repl_suggest_command PRIVATE ../../src)

add_library(repl_prophecy_command SHARED repl_prophecy_command.cpp)
target_include_directories(repl_prophecy_command PRIVATE ../../src)

add_library(glyph_prophecy_stack_void_division SHARED stack_void_division.cpp)
target_include_directories(glyph_prophecy_stack_void_division PRIVATE ../../src)

add_library(prophecy_op SHARED prophecy_op.cpp)
target_include_directories(prophecy_op PRIVATE ../../src)

add_library(prophecy_op SHARED prophecy_op.cpp)
target_include_directories(prophecy_op PRIVATE ../../src)

add_library(stack_slayer_op SHARED stack_slayer_op.cpp)
target_include_directories(stack_slayer_op PRIVATE ../../src)

add_library(egg_op SHARED egg_op.cpp)
target_include_directories(egg_op PRIVATE ../../src)

add_library(glyph_prophecy_op SHARED glyph_prophecy_op.cpp)
target_include_directories(glyph_prophecy_op PRIVATE ../../src)

add_library(omega_op SHARED omega_op.cpp)
target_include_directories(omega_op PRIVATE ../../src)

add_library(sigil_map_op SHARED sigil_map_op.cpp)
target_include_directories(sigil_map_op PRIVATE ../../src)

add_library(entropy_op SHARED entropy_op.cpp)
target_include_directories(entropy_op PRIVATE ../../src)

add_library(void_division_op SHARED void_division_op.cpp)
target_include_directories(void_division_op PRIVATE ../../src)

add_library(duality_op SHARED duality_op.cpp)
target_include_directories(duality_op PRIVATE ../../src)

add_library(over_unity_op SHARED over_unity_op.cpp)
target_include_directories(over_unity_op PRIVATE ../../src)

add_library(prophecy_chain_op SHARED prophecy_chain_op.cpp)
target_include_directories(prophecy_chain_op PRIVATE ../../src)

add_library(forbidden_echo_op SHARED forbidden_echo_op.cpp)
target_include_directories(forbidden_echo_op PRIVATE ../../src)

add_library(math_greek SHARED math_greek.cpp)
target_include_directories(math_greek PRIVATE ../../src)

add_library(crypto_ops SHARED crypto_ops.cpp)
target_include_directories(crypto_ops PRIVATE ../../src)

add_library(chemistry_ops SHARED chemistry_ops.cpp)
target_include_directories(chemistry_ops PRIVATE ../../src)

add_library(learning_mode SHARED learning_mode.cpp)
target_include_directories(learning_mode PRIVATE ../../src)

add_library(logic_ops SHARED logic_ops.cpp)
target_include_directories(logic_ops PRIVATE ../../src)

add_library(fractal_ops SHARED fractal_ops.cpp)
target_include_directories(fractal_ops PRIVATE ../../src)

add_library(quantum_ops SHARED quantum_ops.cpp)
target_include_directories(quantum_ops PRIVATE ../../src)

add_library(kanji_ops SHARED kanji_ops.cpp)
target_include_directories(kanji_ops PRIVATE ../../src)

add_library(music_ops SHARED music_ops.cpp)
target_include_directories(music_ops PRIVATE ../../src)

add_library(glyph_rain SHARED glyph_rain.cpp)
target_include_directories(glyph_rain PRIVATE ../../src)

