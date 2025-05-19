// woflang_config.h
#pragma once

// Version information
#define WOFLANG_VERSION_MAJOR 0
#define WOFLANG_VERSION_MINOR 1
#define WOFLANG_VERSION_PATCH 0

// System configuration
#define WOFLANG_MAX_OPERANDS 10
#define WOFLANG_MAX_EXPRESSION_LENGTH 1000
#define WOFLANG_MAX_IDENTIFIER_LENGTH 50

// Feature toggles
#define WOFLANG_ENABLE_DEBUG 1
#define WOFLANG_ENABLE_LOGGING 1
#define WOFLANG_ENABLE_PLUGINS 1

// Platform-specific configurations
#if defined(_WIN32) || defined(_WIN64)
    #define WOFLANG_PLATFORM_WINDOWS
    #define WOFLANG_PATH_SEPARATOR "\\"
#else
    #define WOFLANG_PLATFORM_UNIX
    #define WOFLANG_PATH_SEPARATOR "/"
#endif

// Unicode support configuration
#define WOFLANG_UNICODE_ENABLED 1
#define WOFLANG_MAX_UTF8_LENGTH 4

// Memory configuration
#define WOFLANG_DEFAULT_BUFFER_SIZE 4096
#define WOFLANG_MAX_STRING_LENGTH 1024

// Thread safety configuration
#define WOFLANG_THREAD_SAFE 1
#define WOFLANG_MAX_THREADS 4

// Plugin configuration
#define WOFLANG_PLUGIN_PATH "./plugins"
#define WOFLANG_MAX_PLUGINS 10

// Error handling configuration
#define WOFLANG_MAX_ERROR_MESSAGE_LENGTH 256
#define WOFLANG_MAX_ERROR_STACK 10

namespace woflang {
    // System-wide type definitions
    using CommandId = unsigned int;
    using ErrorCode = int;
    using PluginId = unsigned int;
    
    // System limits as constexpr
    constexpr size_t MAX_OPERANDS = WOFLANG_MAX_OPERANDS;
    constexpr size_t MAX_EXPRESSION_LENGTH = WOFLANG_MAX_EXPRESSION_LENGTH;
    constexpr size_t MAX_IDENTIFIER_LENGTH = WOFLANG_MAX_IDENTIFIER_LENGTH;
    
    // Version information as constexpr
    constexpr struct Version {
        int major = WOFLANG_VERSION_MAJOR;
        int minor = WOFLANG_VERSION_MINOR;
        int patch = WOFLANG_VERSION_PATCH;
    } VERSION;
}