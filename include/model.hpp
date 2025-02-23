#pragma once
#include <shader.hpp>
#include <mesh.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
    // Model data
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    Model(std::string const& path, bool gamma = false) : gammaCorrection(gamma) {
        loadModel(path);
    }
    void Draw(Shader&);
private:
    void loadModel(std::string const&);
    void processNode(aiNode*, const aiScene*);
    Mesh processMesh(aiMesh*, const aiScene*);
    std::vector<Texture> loadMaterialTextures(aiMaterial*, aiTextureType, std::string);
};