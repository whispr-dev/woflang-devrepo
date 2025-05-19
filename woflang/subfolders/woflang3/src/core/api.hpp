#pragma once

#include "core/woflang.hpp"  // bring in full interpreter definition

// Macro to export plugin ops across platforms
#ifndef WOFLANG_PLUGIN_EXPORT
#   if defined(_WIN32) || defined(_WIN64)
#       define WOFLANG_PLUGIN_EXPORT extern "C" __declspec(dllexport)
#   else
#       define WOFLANG_PLUGIN_EXPORT extern "C"
#   endif
#endif

// Macro for easy op registration inside plugins
#define REGISTER_OP(name, lambda) \
    interpreter.register_op(name, lambda)
