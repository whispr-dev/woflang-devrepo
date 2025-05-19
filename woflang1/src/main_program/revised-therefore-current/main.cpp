// `main.cpp` attempt at a C+++ version of woflang

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <cmath>
#include "commands.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <functional>


// Define CommandType enum or include it from its header file
// enum CommandType {
//     CMD_ADD,
//    CMD_SUB,
    // Add other command types...
//    CMD_UNKNOWN


// Define a type for command functions
typedef std::function<void(double*, int)> CommandFunction;

// Command map to hold the loaded dictionary
std::unordered_map<std::string, CommandFunction> commandMap;

// Function to load dictionary from file
bool loadDictionary(const std::string& filename);

// Function to execute a command
void executeCommand(const std::string& commandType, double* operands, int numOperands) {
    auto it = commandMap.find(commandType);
    if (it != commandMap.end()) {
        it->second(operands, numOperands);
    } else {
        std::cerr << "Unknown command: " << commandType << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // Check for dictionary file input
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <dictionary_file>" << std::endl;
        return 1;
    }

    std::string dictionaryFile = argv[1];
    if (!loadDictionary(dictionaryFile)) {
        return 1;
    }

    // Sample operands for demonstration
    double operands[] = {5.0, 3.0};
    int numOperands = 2;

    // Sample command execution
    executeCommand("CMD_ADD", operands, numOperands); // Assume CMD_ADD is a key in the loaded dictionary

    return 0;
}

// Function declarations
void printError(const char* message);
CommandType parseCommand(const std::string& commandStr);
double clamp(double value, double min, double max);
void createThread(const std::function<void()>& task);
void joinAllThreads();

// Global Constants
const double PI = 3.14159265358979323846264338327950288419716939937510;
std::vector<double> buffer(4, 0.0);  // Buffer for SIMD-like operations

// Thread Control Variables
std::atomic<int> current_thread_id{0};
const int MAX_THREADS = 4;
std::vector<std::thread> threads;
std::mutex mutex_lock;
std::condition_variable cv;
std::atomic<bool> is_thread_ready{false};

// Function to process input commands
void processInputCommands() {
    std::string command;
    std::cout << "Enter command: ";
    std::getline(std::cin, command);

    CommandType commandType = parseCommand(command); // Placeholder for actual parsing logic
    double operands[2] = {3.0, 5.0}; // Simulated parsed operands

    executeCommand(commandType, operands, 2);
}

// Function to execute a command based on type
void executeCommand(CommandType commandType, double* operands, int numOperands) {
    auto it = commandMap.find(commandType);
    if (it != commandMap.end()) {
        it->second(operands, numOperands);
    } else {
        std::cerr << "Unknown command" << std::endl;
    }
}

// Function to create a thread
void create_thread()
    if (threads.size() < MAX_THREADS)
        threads.emplace_back([]()
            std::unique_lock<std::mutex> lk(mutex_lock);
            cv.wait(lk, [] { return is_thread_ready.load(); });
            std::cout << "Thread running with ID: " << current_thread_id++ << std::endl;
        });
        std::cout << "Thread created with ID: " << threads.size() - 1 << std::endl;
    else 
        std::cerr << "Max threads reached, cannot create more." << std::endl;
    

// Function to join threads
void join_thread() {
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
            std::cout << "Thread joined." << std::endl;
        }
    }
}

// Function to lock mutex
void lock_mutex() {
    mutex_lock.lock();
    std::cout << "Mutex locked." << std::endl;
}

// Function to unlock mutex
void unlock_mutex() {
    mutex_lock.unlock();
    std::cout << "Mutex unlocked." << std::endl;
}

// Main routine using buffer for SIMD-like operations
void main_routine() {
    buffer[0] += buffer[1];
}

// Initialization function
void initialization() {
    // Initialize buffer and other settings
    buffer[0] = PI;
}

// Plugin loader function
v// oid plugin_loader() {
//
    // Implement module loading logic if necessary
// }

// Function to read and parse program file
//? void readProgramFile(const std::string& filename, std::unordered_map<std::string, double>& weights, std::vector<std::string>& operations) {
//?     std::ifstream file(filename);
//?     if (!file.is_open()) {
//?         std::cerr << "Error opening file: " << filename << std::endl;
//?        return;
//?         }
//? }

    std::string line;
    bool inWeightsSection = false;
    bool inNetworkSection = false;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == ';') continue; // Skip empty lines and comments

        if (line.find("[WEIGHTS]") != std::string::npos) {
            inWeightsSection = true;
            inNetworkSection = false;
        } else if (line.find("[NETWORK]") != std::string::npos) {
            inWeightsSection = false;
            inNetworkSection = true;
        } else if (line == "0x00") {
            inWeightsSection = false;
            inNetworkSection = false;
        } else if (inWeightsSection) {
            std::istringstream iss(line);
            std::string key;
            double value;
            if (iss >> key >> value) {
                weights[key] = value;
            }
        } else if (inNetworkSection) {
            operations.push_back(line);
        }

    file.close();
}

// {
// Function to execute a network operation
// void executeOperation(const std::string& operation, const std::unordered_map<std::string, double>& weights) {
    // Translate operation symbols into corresponding commands
//    if (operation.find("AND") != std::string::npos) {
        // Extract operands and perform AND operation
//    } else if (operation.find("OR") != std::string::npos) {
        // Extract operands and perform OR operation
//    }
    // Continue for other operations (NAND, XOR, etc.)


{
    std::unordered_map<std::string, double> weights;
    std::vector<std::string> operations;

    // Read and parse the program file
    readProgramFile("a_program.txt", weights, operations);

    // Execute operations based on parsed data
    for (const auto& operation : operations) {
        executeOperation(operation, weights);
    }

    return 0;
}

// Register commands function
void register_commands() {
    // Implement command registration logic if necessary
}

// Function to add two doubles
void add_double(double* a, double* b) {
    *a += *b;
};

    initialization();
    processInputCommands(); // Start processing input commands

    double operands[] = {5.0, 3.0};
    int numOperands = 2;
    
//    executeCommand(CMD_ADD, operands, numOperands); // Should output the result of 5 + 3
 //   executeCommand(CMD_DIV, operands, numOperands); // Should output the result of 5 / 3

int main() {
    initialization();
    processInputCommands(); // Start processing input commands

    create_thread();
    lock_mutex();
    unlock_mutex();
    join_thread();

    return 0;
    }
