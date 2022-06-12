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
    glm::vec3 tangent;   // [not used] tangent
    glm::vec3 bitangent; // [not used] bitangent

    int   m_BoneIDs[MAX_BONE_INFLUENCE]; // bone indexes which will influence this vertex
    float m_Weights[MAX_BONE_INFLUENCE]; // weights from each bone
} Vertex;

class Mesh {
  public:
    // mesh Data
    std::vector<Vertex>  vertices;
    std::vector<GLuint>  indices;
    std::vector<Texture> textures;
    unsigned int         VAO;

    glm::vec3 pos;      // position of Mesh object.
    glm::vec3 scale;    // scale the Mesh Object.
    glm::vec3 rotation; // rotation angle.

    // default constructor
    Mesh();

    // constructor
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    // default deconstructor
    ~Mesh();

    // render the mesh
    void Draw(Shader& shader);

    // get render matrix.
    glm::mat4 GetModelMatrix();

  private:
    // render data
    unsigned int VBO, EBO;

    // initializes all the buffer objects/arrays
    void setupMesh();
};

Mesh GetBoxMesh();
Mesh GetPlaneMesh(int axis=2);
Mesh GetPyramidMesh();