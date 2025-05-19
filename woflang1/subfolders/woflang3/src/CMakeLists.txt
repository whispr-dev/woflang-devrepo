file(GLOB CORE_SRC core/*.cpp ops/*.cpp glyph/*.cpp repl/*.cpp simd/*.cpp io/*.cpp)
add_library(woflang_core ${CORE_SRC})
target_include_directories(woflang_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core ${CMAKE_CURRENT_SOURCE_DIR}/ops ${CMAKE_CURRENT_SOURCE_DIR}/glyph ${CMAKE_CURRENT_SOURCE_DIR}/repl ${CMAKE_CURRENT_SOURCE_DIR}/simd ${CMAKE_CURRENT_SOURCE_DIR}/io)

add_executable(woflang_repl repl/repl_main.cpp)
target_link_libraries(woflang_repl PRIVATE woflang_core)
