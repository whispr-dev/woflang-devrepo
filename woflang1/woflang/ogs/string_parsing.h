// `string_parsing.h` C++ attempt at woflang

#pragma once
#include <string>
#include <vector>


// Error handling for string parsing operations
void handleStringErrors(const std::string& operation, int errorCode);

// Function declarations

// Function to concatenate two strings
std::string concatenateStrings(const std::string& str1, const std::string& str2);

// Function to find a substring within a string
int findSubstring(const std::string& mainStr, const std::string& toFind);

// Function to replace a substring within a string
std::string replaceSubstring(const std::string& mainStr, const std::string& toReplace, const std::string& replaceWith);

// Function to convert string to uppercase
std::string toUpperCase(const std::string& str);

// Function to convert string to lowercase
std::string toLowerCase(const std::string& str);

// Function to split a string into a vector based on a delimiter
std::vector<std::string> splitString(const std::string& str, char delimiter);

// Function to trim whitespace from both ends of a string
std::string trimString(const std::string& str);

// Function to handle and report string parsing errors
void reportStringError(const std::string& functionName, int errorCode);
