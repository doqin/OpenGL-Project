#include <readFile.hpp>
#include <fstream>
#include <sstream>

std::string readFile(const std::string& filePath) {
    std::ifstream file(filePath); // Open the file
    std::stringstream buffer; // Create a buffer to store the file content
    buffer << file.rdbuf(); // Read the file content
    return buffer.str(); // Return the file content
}