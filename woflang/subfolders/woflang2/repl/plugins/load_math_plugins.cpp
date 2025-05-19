// load_math_plugins.cpp
// Auto-registers all math plugin modules

#include "wof_interpreter.hpp"
#include <filesystem>
#include <iostream>
#include <dlfcn.h>  // For dynamic loading if needed later

namespace fs = std::filesystem;

// Forward declare known registration functions
void register_-1-overview_of_advanced_math_moule_plugin(WofInterpreter&);
void register_-calculus_and_graph_theory_plugin(WofInterpreter&);
void register_0-contents#_of_this_archive_plugin(WofInterpreter&);
void register_0-i-what_should_be_in_adv_math_plugin(WofInterpreter&);
void register_0-ii-how_to_.make_mathlib-1_module_plugin(WofInterpreter&);
void register_10-i-moar_symbolic_dif_and_int_plugin(WofInterpreter&);
void register_10-ii-algebraic_expression_reduction_plugin(WofInterpreter&);
void register_10-symbolic_calculus_plugin(WofInterpreter&);
void register_11-complex_number_processing_plugin(WofInterpreter&);
void register_11-i-complex_logarithms_plugin(WofInterpreter&);
void register_11-ii-complex_exponentiation_plugin(WofInterpreter&);
void register_11-iii-complex_trigonometric_functions_plugin(WofInterpreter&);
void register_12-cryptographic_functions_plugin(WofInterpreter&);
void register_12-i-modular_exponentiation_plugin(WofInterpreter&);
void register_12-ii-prime_testing_and_generation_plugin(WofInterpreter&);
void register_15-discrete_math_functions_plugin(WofInterpreter&);
void register_15-i-combinatorial_logic_and_permutations_plugin(WofInterpreter&);
void register_15-i-igraph_colouring_plugin(WofInterpreter&);
void register_15-i-permutations_of_arrangements_plugin(WofInterpreter&);
void register_15-iii-sorting_and_something_algorithms_plugin(WofInterpreter&);
void register_3-advanced_stats_module_plugin(WofInterpreter&);
void register_5-i-numerical_integration_plugin(WofInterpreter&);
void register_5-ii-differentiartion_the_numerical_style_plugin(WofInterpreter&);
void register_5-ii-numerical_differentianion_plugin(WofInterpreter&);
void register_5-iii-gradient_and_hessian_plugin(WofInterpreter&);
void register_8-i-shortest_path_algorithms_plugin(WofInterpreter&);
void register_8-ii-fast_searching_graphs_plugin(WofInterpreter&);
void register_8-ii-graphing_and_efficiency_plugin(WofInterpreter&);
void register_8-iii-more_shoortest_path_algporithms_plugin(WofInterpreter&);
void register_9-advanced_trigonometry_and_geometry_plugin(WofInterpreter&);
void register_9-i-spherical_trigonometry_plugin(WofInterpreter&);
void register_9-ii-geometric_transformations_plugin(WofInterpreter&);
void register_9-iii-something_about_hulls_plugin(WofInterpreter&);
void register_x-unicode_advanced_math_library_plugin(WofInterpreter&);

void load_all_math_plugins(WofInterpreter& vm) {
    register_-1-overview_of_advanced_math_moule_plugin(vm);  // from -1-overview_of_advanced_math_moule
    register_-calculus_and_graph_theory_plugin(vm);  // from -calculus_and_graph_theory
    register_0-contents#_of_this_archive_plugin(vm);  // from 0-contents#_of_this_archive
    register_0-i-what_should_be_in_adv_math_plugin(vm);  // from 0-i-what_should_be_in_adv_math
    register_0-ii-how_to_.make_mathlib-1_module_plugin(vm);  // from 0-ii-how_to_.make_mathlib-1_module
    register_10-i-moar_symbolic_dif_and_int_plugin(vm);  // from 10-i-moar_symbolic_dif_and_int
    register_10-ii-algebraic_expression_reduction_plugin(vm);  // from 10-ii-algebraic_expression_reduction
    register_10-symbolic_calculus_plugin(vm);  // from 10-symbolic_calculus
    register_11-complex_number_processing_plugin(vm);  // from 11-complex_number_processing
    register_11-i-complex_logarithms_plugin(vm);  // from 11-i-complex_logarithms
    register_11-ii-complex_exponentiation_plugin(vm);  // from 11-ii-complex_exponentiation
    register_11-iii-complex_trigonometric_functions_plugin(vm);  // from 11-iii-complex_trigonometric_functions
    register_12-cryptographic_functions_plugin(vm);  // from 12-cryptographic_functions
    register_12-i-modular_exponentiation_plugin(vm);  // from 12-i-modular_exponentiation
    register_12-ii-prime_testing_and_generation_plugin(vm);  // from 12-ii-prime_testing_and_generation
    register_15-discrete_math_functions_plugin(vm);  // from 15-discrete_math_functions
    register_15-i-combinatorial_logic_and_permutations_plugin(vm);  // from 15-i-combinatorial_logic_and_permutations
    register_15-i-igraph_colouring_plugin(vm);  // from 15-i-igraph_colouring
    register_15-i-permutations_of_arrangements_plugin(vm);  // from 15-i-permutations_of_arrangements
    register_15-iii-sorting_and_something_algorithms_plugin(vm);  // from 15-iii-sorting_and_something_algorithms
    register_3-advanced_stats_module_plugin(vm);  // from 3-advanced_stats_module
    register_5-i-numerical_integration_plugin(vm);  // from 5-i-numerical_integration
    register_5-ii-differentiartion_the_numerical_style_plugin(vm);  // from 5-ii-differentiartion_the_numerical_style
    register_5-ii-numerical_differentianion_plugin(vm);  // from 5-ii-numerical_differentianion
    register_5-iii-gradient_and_hessian_plugin(vm);  // from 5-iii-gradient_and_hessian
    register_8-i-shortest_path_algorithms_plugin(vm);  // from 8-i-shortest_path_algorithms
    register_8-ii-fast_searching_graphs_plugin(vm);  // from 8-ii-fast_searching_graphs
    register_8-ii-graphing_and_efficiency_plugin(vm);  // from 8-ii-graphing_and_efficiency
    register_8-iii-more_shoortest_path_algporithms_plugin(vm);  // from 8-iii-more_shoortest_path_algporithms
    register_9-advanced_trigonometry_and_geometry_plugin(vm);  // from 9-advanced_trigonometry_and_geometry
    register_9-i-spherical_trigonometry_plugin(vm);  // from 9-i-spherical_trigonometry
    register_9-ii-geometric_transformations_plugin(vm);  // from 9-ii-geometric_transformations
    register_9-iii-something_about_hulls_plugin(vm);  // from 9-iii-something_about_hulls
    register_x-unicode_advanced_math_library_plugin(vm);  // from x-unicode_advanced_math_library
}
