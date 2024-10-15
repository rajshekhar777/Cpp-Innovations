#include "FileExplorer.h"
#include <iostream>
#include <filesystem>
#include <regex>

// Using the C++17 filesystem library
namespace fs = std::filesystem;

// Function to list files and directories
void FileExplorer::listDirectory(const std::string &path, bool showHidden) {
    try {
        for (const auto &entry : fs::directory_iterator(path)) {
            std::string filename = entry.path().filename().string();
            if (showHidden || !isHiddenFile(filename)) {
                std::cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << filename << std::endl;
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Function to search files based on a pattern
void FileExplorer::searchFiles(const std::string &path, const std::string &pattern) {
    std::regex regexPattern(pattern);
    try {
        for (const auto &entry : fs::recursive_directory_iterator(path)) {
            if (fs::is_regular_file(entry.path())) {
                std::string filename = entry.path().filename().string();
                if (patternMatch(filename, pattern)) {
                    std::cout << "Match Found: " << entry.path() << std::endl;
                }
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Function to navigate to a specified directory
void FileExplorer::navigate(const std::string &path) {
    try {
        if (fs::is_directory(path)) {
            fs::current_path(path);
            std::cout << "Current directory changed to: " << fs::current_path() << std::endl;
        } else {
            std::cerr << "Error: Invalid directory path.\n";
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Helper function to check if a file is hidden
bool FileExplorer::isHiddenFile(const std::string &filename) {
    return (!filename.empty() && filename[0] == '.');
}

// Helper function to match the file pattern
bool FileExplorer::patternMatch(const std::string &filename, const std::string &pattern) {
    std::regex regexPattern(pattern);
    return std::regex_search(filename, regexPattern);
}
