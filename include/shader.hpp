#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>

// Shader class
class Shader {
public:
    // The program ID
    unsigned int ID;

    // Constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // Destructor
    ~Shader();
    // Use/activate the shader
    void use();
    // Utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setMat4(const std::string& name, glm::mat4 value) const;
};