#pragma once

#include "Base.hh"
#include "Buffer.hh"
#include "Shader.hh"
#include "Texture.hh"

#define MAX_BONE_INFLUENCE 4
typedef struct Vertex {
    glm::vec3 pos;       // point of vertex.
    glm::vec3 normal;    // normal of vertex.
    glm::vec2 coord;     // texture coord.
    glm::vec3 color;     // [not used] color of vertex.
    glm::vec3 tangent;   // [not used] tangent
    glm::vec3 bitangent; // [not used] bitangent

    int   m_BoneIDs[MAX_BONE_INFLUENCE]; // bone indexes which will influence this vertex
    float m_Weights[MAX_BONE_INFLUENCE]; // weights from each bone
} Vertex;

struct iTexture {
    unsigned int id;
    std::string  type;
    std::string  path;
};

class Mesh {
  public:
    // mesh Data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<iTexture>     textures;
    unsigned int              VAO;

    // default constructor
    Mesh() {}

    // constructor
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<iTexture> textures);

    // default deconstructor
    ~Mesh() {}

    // render the mesh
    void Draw(Shader& shader);

  private:
    // render data
    unsigned int VBO, EBO;

    // initializes all the buffer objects/arrays
    void setupMesh();
};