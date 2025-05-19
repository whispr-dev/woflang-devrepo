// utils.cpp
#include "utils.h"
#include <iostream>

void printError(const char* message) {
    std::cerr << "Error: " << message << std::endl;
}


// utils.cpp

#include "utils.h"
#include <iostream>
#include <unordered_map>

void printError(const char* message) {
    std::cerr << "Error: " << message << std::endl;
}

CommandType parseCommand(const std::string& commandStr) {
    static std::unordered_map<std::string, CommandType> commandMap = {
        {"ADD", CMD_ADD},
        {"SUB", CMD_SUB},
        // Add more mappings here
    };

    auto it = commandMap.find(commandStr);
    if (it != commandMap.end()) {
        return it->second;
    } else {
        printError("Unknown command");
        return CMD_UNKNOWN;  // Define CMD_UNKNOWN for error handling
    }
}



// utils.cpp

#include "utils.h"
#include <algorithm>  // For std::min and std::max

double clamp(double value, double min, double max) {
    return std::max(min, std::min(max, value));
}



// utils.cpp

#include "utils.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

std::vector<std::thread> threads;
std::mutex mutex_lock;
std::condition_variable cv;
std::atomic<bool> is_thread_ready{false};

void createThread(const std::function<void()>& task) {
    threads.emplace_back(task);
}

void joinAllThreads() {
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}


// utils.h

#pragma once
#include <string>
#include <vector>
#include <functional>
#include <thread>

// Error handling
void printError(const char* message);

// Command parsing
CommandType parseCommand(const std::string& commandStr);

// Math utilities
double clamp(double value, double min, double max);

// Thread management
void createThread(const std::function<void()>& task);
void joinAllThreads();
