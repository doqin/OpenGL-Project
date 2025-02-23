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
    Shader(const char*, const char*);
    // Destructor
    ~Shader();
    // Use/activate the shader
    void use();
    // Utility uniform functions
    void setBool(const std::string&, bool) const;
    void setInt(const std::string&, int) const;
    void setFloat(const std::string&, float) const;
    void setVec3(const std::string&, float, float, float) const;
    void setVec3(const std::string&, glm::vec3) const;
    void setMat4(const std::string&, glm::mat4) const;
};