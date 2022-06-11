#pragma once

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#include "Base.hh"
#include "Mesh.hh"
#include "Shader.hh"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class Model {
  public:
    // model data
    vector<iTexture> textures_loaded; // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh>     meshes;          // all meshes.
    string           directory;       // model path.
    bool             gammaCorrection;

    // default constructor.
    Model() {}

    // constructor, expects a filepath to a 3D model.
    Model(string const& path, bool gamma = false);

    // default deconstructor.
    ~Model() {}

    // draws the model, and thus all its meshes
    void Draw(Shader& shader);

  private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string const& path);

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, const aiScene* scene);

    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a iTexture struct.
    vector<iTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);