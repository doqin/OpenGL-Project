#pragma once
#include <shader.hpp>
#include <vertex.hpp>
#include <texture.hpp>

#include <vector>

class Mesh {
public:
    // Mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO;

    Mesh(std::vector<Vertex>, std::vector<unsigned int>, std::vector<Texture>);
    void Draw(Shader&);
private:
    // Render data
    unsigned int VBO, EBO;

    void setupMesh();
};