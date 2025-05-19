// WoflangPlugin.h
#pragma once

#include <string>
#include <vector>

class WoflangPlugin {
    public:
        virtual ~WoflangPlugin() = default;
        
        // Add initialization context
        struct InitContext {
            const CommandSystem& cmdSystem;
            const CommandDictionary& dict;
            ErrorSystem& errorSystem;
        };
        
        virtual bool initialize(const InitContext& context) = 0;
        virtual void cleanup() = 0;
        
        // Add result context for better error handling
        struct ExecuteResult {
            bool success;
            std::string error;
            double value;
        };
        
        virtual ExecuteResult execute(const std::string& command, 
                                    const std::vector<double>& arguments) = 0;
    protected:
        // Add helper methods for plugins
        bool validateArguments(size_t expected, size_t received);
        void logOperation(const std::string& op, bool success);
    };

// FuzzyLogicPlugin.h
#pragma once

#include "WoflangPlugin.h"

class FuzzyLogicPlugin : public WoflangPlugin {
public:
    void initialize() override;
    void cleanup() override;
    void execute(const std::string& command, double& result, const std::vector<double>& arguments) override;

private:
    // Fuzzy logic operations...
    void binaryToFuzzy(double& value);
    void fuzzyToBinary(double& value);
    void orRoutine(double& a, double b);
    // ... other fuzzy logic operations ...
};

// FuzzyLogicPlugin.cpp
#include "FuzzyLogicPlugin.h"

void FuzzyLogicPlugin::initialize() {
    // Initialization code for FuzzyLogicPlugin
}

void FuzzyLogicPlugin::cleanup() {
    // Cleanup code for FuzzyLogicPlugin
}

void FuzzyLogicPlugin::execute(const std::string& command, double& result, const std::vector<double>& arguments) {
    if (command == "binaryToFuzzy") {
        // Code for binaryToFuzzy operation
    } else if (command == "fuzzyToBinary") {
        // Code for fuzzyToBinary operation
    } else if (command == "orRoutine") {
        // Code for orRoutine operation
    }
    // ... handle other fuzzy logic operations ...
}

void FuzzyLogicPlugin::binaryToFuzzy(double& value) {
    // Implementation of binaryToFuzzy
}

void FuzzyLogicPlugin::fuzzyToBinary(double& value) {
    // Implementation of fuzzyToBinary
}

void FuzzyLogicPlugin::orRoutine(double& a, double b) {
    // Implementation of orRoutine
}

// ... implementations of other fuzzy logic operations ...

// AdvancedMathPlugin.h
#pragma once

#include "WoflangPlugin.h"

class AdvancedMathPlugin : public WoflangPlugin {
public:
    void initialize() override;
    void cleanup() override;
    void execute(const std::string& command, double& result, const std::vector<double>& arguments) override;

private:
    // Advanced math operations...
    void matrixMultiply(const std::vector<double>& mat1, const std::vector<double>& mat2, std::vector<double>& result);
    void matrixTranspose(const std::vector<double>& mat, std::vector<double>& result);
    void matrixInverse(const std::vector<double>& mat, std::vector<double>& result);
    // ... other advanced math operations ...
};

// AdvancedMathPlugin.cpp
#include "AdvancedMathPlugin.h"

void AdvancedMathPlugin::initialize() {
    // Initialization code for AdvancedMathPlugin
}

void AdvancedMathPlugin::cleanup() {
    // Cleanup code for AdvancedMathPlugin
}

void AdvancedMathPlugin::execute(const std::string& command, double& result, const std::vector<double>& arguments) {
    if (command == "matrixMultiply") {
        // Code for matrixMultiply operation
    } else if (command == "matrixTranspose") {
        // Code for matrixTranspose operation
    } else if (command == "matrixInverse") {
        // Code for matrixInverse operation
    }
    // ... handle other advanced math operations ...
}

void AdvancedMathPlugin::matrixMultiply(const std::vector<double>& mat1, const std::vector<double>& mat2, std::vector<double>& result) {
    // Implementation of matrixMultiply
}

void AdvancedMathPlugin::matrixTranspose(const std::vector<double>& mat, std::vector<double>& result) {
    // Implementation of matrixTranspose
}

void AdvancedMathPlugin::matrixInverse(const std::vector<double>& mat, std::vector<double>& result) {
    // Implementation of matrixInverse
}

class IPlugin {
    public:
        virtual ~IPlugin() = default;
        virtual bool initialize() = 0;
        virtual std::string_view getName() const = 0;
        virtual void registerCommands(CommandRegistry&) = 0;
    };

/ PluginManager.h
class PluginManager {
public:
    void loadPlugins();
    void unloadPlugins();
    void executePlugin(const std::string& pluginName, const std::string& command, double& result, const std::vector<double>& arguments);
private:
    std::unordered_map<std::string, std::unique_ptr<WoflangPlugin>> plugins;
};