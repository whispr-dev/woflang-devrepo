#pragma once
#include "../core/woflang.hpp"

// This header is to be included by any DLL plugin project
struct WoflangPlugin {
    virtual ~WoflangPlugin() = default;
    virtual void register_ops(WoflangInterpreter&) = 0;
};

// For plugin DLLs: extern "C" function for Win32
#define WOFLANG_PLUGIN_EXPORT extern "C" __declspec(dllexport)
