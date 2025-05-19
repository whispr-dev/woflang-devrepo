// utils.h
#pragma once
#include "woflang_config.h"
#include "constants.h"
#include <string>
#include <vector>
#include <functional>

namespace woflang {

// Get system instances
auto& cmdSystem = woflang::CommandSystem::getInstance();
auto& dict = woflang::CommandDictionary::getInstance();
auto& errorSystem = woflang::ErrorSystem::getInstance();

// Print version info
std::cout << "WoflangCPP v" 
          << woflang::VERSION.major << "."
          << woflang::VERSION.minor << "."
          << woflang::VERSION.patch << std::endl;

// Load default dictionary if no file provided
std::string dictFile = (argc > 1) ? argv[1] : woflang::constants::DEFAULT_DICTIONARY_FILE;

class Utils {
public:
    // Math utilities
    static double clamp(double value, double min, double max);
    static bool isApproximatelyEqual(double a, double b, double epsilon = 1e-10);
    static bool isInRange(double value, double min, double max);
    
    // String utilities
    static std::string trim(const std::string& str);
    static std::vector<std::string> split(const std::string& str, char delimiter);
    static bool startsWith(const std::string& str, const std::string& prefix);
    static bool endsWith(const std::string& str, const std::string& suffix);
    
    // Vector operations
    template<typename T>
    static void vectorClamp(std::vector<T>& vec, T min, T max) {
        for (auto& val : vec) {
            val = static_cast<T>(clamp(static_cast<double>(val), 
                                     static_cast<double>(min), 
                                     static_cast<double>(max)));
        }
    }
    
    // File utilities
    static bool fileExists(const std::string& filename);
    static std::string readFileContents(const std::string& filename);
    static bool writeFileContents(const std::string& filename, const std::string& content);
    
    // Debug utilities
    static void debugPrint(const std::string& message);
    static void setDebugMode(bool enabled);

private:
    static bool debugMode;
};

} // namespace woflang