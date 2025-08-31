cmake_minimum_required(VERSION 3.16)

file(GLOB PLUGIN_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*_ops.cpp")
set(_PLUGIN_OUT_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Plugins")

foreach(plugin_src ${PLUGIN_SRCS})
  get_filename_component(base "${plugin_src}" NAME_WE)   # e.g. trig_ops
  add_library(${base} SHARED "${plugin_src}")

  target_include_directories(${base} PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/plugins
  )
  target_link_libraries(${base} PRIVATE woflang_core)
target_compile_options(${base} PRIVATE -include "${CMAKE_SOURCE_DIR}/core/woflang_compat.hpp")

  set_target_properties(${base} PROPERTIES
    OUTPUT_NAME "lib${base}"
    PREFIX ""
    RUNTIME_OUTPUT_DIRECTORY "${_PLUGIN_OUT_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${_PLUGIN_OUT_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${_PLUGIN_OUT_DIR}"
  )
endforeach()
