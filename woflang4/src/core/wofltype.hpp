// src/core/WofType.hpp
#pragma once

namespace woflang {
    // The core value types for WofLang
    enum class WofType {
        Integer,    // Integer values
        Double,     // Floating point values 
        String,     // String values
        Symbol,     // Symbol references
        Unit,       // Values with units
        List        // List of values
    };
}