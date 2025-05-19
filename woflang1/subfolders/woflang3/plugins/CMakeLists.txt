# CMakeLists.txt in plugins/

file(GLOB_RECURSE PLUGIN_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

foreach(plugin_src ${PLUGIN_SRCS})
    # e.g. arts/kanji/kanji_ops.cpp → plugin_name = kanji_ops
    get_filename_component(plugin_name ${plugin_src} NAME_WE)
    add_library(${plugin_name} SHARED ${plugin_src})
    target_include_directories(${plugin_name} PRIVATE ../src/core)
endforeach()
