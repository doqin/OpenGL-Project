#include <readFile.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

std::string readFile(const std::string& path) {
    std::filesystem::path filePath = std::filesystem::path(__FILE__).parent_path() / path;
    std::ifstream file(filePath); // Open the file
    if (file) {
        std::stringstream buffer;
        buffer << file.rdbuf(); // Read the file
        return buffer.str();
    }
    else {
        std::cout << "Failed to open file: " << filePath << std::endl;
        return "";
    }
}