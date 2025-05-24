# Plugins CMakeLists.txt

# Define plugin build function
function(add_woflang_plugin name source)
    add_library(${name} MODULE ${source})
    
    # Include dependencies
    target_include_directories(${name} PRIVATE
        ${CMAKE_SOURCE_DIR}/src/core
        ${CMAKE_SOURCE_DIR}/src/io
        ${CMAKE_SOURCE_DIR}/src/simd
    )
    
    # Link against core library
    target_link_libraries(${name} PRIVATE woflang_core)
    
    # Set output directory
    set_target_properties(${name} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
    )
    
    # Add installation rule
    install(TARGETS ${name}
        LIBRARY DESTINATION plugins
        RUNTIME DESTINATION plugins
    )
    
    # Add dependency on plugin directory
    add_dependencies(${name} plugin_directory)
endfunction()

# Add our fixed plugins
add_woflang_plugin(math_ops plugins/math_ops.cpp)
add_woflang_plugin(crypto_ops plugins/crypto_ops.cpp)
add_woflang_plugin(fractal_ops plugins/fractal_ops.cpp)
add_woflang_plugin(quantum_ops plugins/quantum_ops.cpp)

# Additional plugins can be added here as they're implemented
# add_woflang_plugin(symbolic_ops plugins/symbolic_ops.cpp)
# add_woflang_plugin(kanji_ops plugins/kanji_ops.cpp)