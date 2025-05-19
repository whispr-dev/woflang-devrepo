// utils.cpp
#include "woflang_config.h"
#include "constants.h"
#include "utils.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

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

bool Utils::debugMode = false;

double Utils::clamp(double value, double min, double max) {
    return std::min(std::max(value, min), max);
}

bool Utils::isApproximatelyEqual(double a, double b, double epsilon) {
    return std::abs(a - b) < epsilon;
}

bool Utils::isInRange(double value, double min, double max) {
    return value >= min && value <= max;
}

std::string Utils::trim(const std::string& str) {
    auto start = std::find_if_not(str.begin(), str.end(), ::isspace);
    auto end = std::find_if_not(str.rbegin(), str.rend(), ::isspace).base();
    return (start < end ? std::string(start, end) : std::string());
}

std::vector<std::string> Utils::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(trim(token));
        }
    }
    return tokens;
}

bool Utils::startsWith(const std::string& str, const std::string& prefix) {
    return str.size() >= prefix.size() && 
           str.compare(0, prefix.size(), prefix) == 0;
}

bool Utils::endsWith(const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size() && 
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool Utils::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

std::string Utils::readFileContents(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }
    return std::string((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
}

bool Utils::writeFileContents(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    file << content;
    return file.good();
}

void Utils::debugPrint(const std::string& message) {
    if (debugMode) {
        std::cerr << "[DEBUG] " << message << std::endl;
    }
}

void Utils::setDebugMode(bool enabled) {
    debugMode = enabled;
}

} // namespace woflang