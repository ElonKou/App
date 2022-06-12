/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : Mesh.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Tue Jun  7 21:10:32 2022
================================================================*/

#include "Mesh.hh"

Mesh::Mesh() {
    pos      = glm::vec3(0.0f);
    scale    = glm::vec3(1.0);
    rotation = glm::vec3(0.0, 0.0, 0.0); // [Eular] default rotation.
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->vertices = vertices;
    this->indices  = indices;
    this->textures = textures;

    pos      = glm::vec3(0.0f);
    scale    = glm::vec3(1.0);
    rotation = glm::vec3(0.0, 0.0, 0.0); // [Eular] default rotation.

    // now that we have all the required data, set the vertex buffers and its attribute pointers.
    setupMesh();
}

Mesh::~Mesh() {}

void Mesh::Draw(Shader& shader) {
    // bind appropriate textures
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string

        // now set the sampler to the correct texture unit
        // glUniform1i(glGetUniformLocation(shader.Program, (name + number).c_str()), i);
        // and finally bind the texture
        // glBindTexture(GL_TEXTURE_2D, textures[i].id);

        textures[i].Bind();
        shader.Set1i(name + number, textures[i].id);
    }

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

glm::mat4 Mesh::GetModelMatrix() {
    glm::mat4 model1 = glm::mat4(1.0f);
    glm::mat4 model2 = glm::mat4(1.0f);
    glm::mat4 model3 = glm::mat4(1.0f);
    model1           = glm::scale(model1, scale);
    model2           = glm::rotate(model2, rotation.z, glm::vec3(0.0, 0.0, 1.0));
    model2           = glm::rotate(model2, rotation.x, glm::vec3(1.0, 0.0, 0.0));
    model2           = glm::rotate(model2, rotation.y, glm::vec3(0.0, 1.0, 0.0));
    model3           = glm::translate(model3, pos);

    glm::quat q = glm::quat(rotation);
    glm::mat4 R = glm::toMat4(q);

    // std::cout << "model1: " << std::endl
    //           << model1 << std::endl;
    // std::cout << "model2: " << std::endl
    //           << model2 << std::endl;
    // std::cout << "model3: " << std::endl
    //           << model3 << std::endl;
    // std::cout << "pos: " << pos << std::endl;
    // return model3 * model2 * model1;
    return model3 * R * model1;
}

void Mesh::setupMesh() {
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, coord));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
    // ids
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

    // weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
    glBindVertexArray(0);
}

// typedef struct Vertex {
//     glm::vec3 pos;       // point of vertex.
//     glm::vec3 normal;    // normal of vertex.
//     glm::vec2 coord;     // texture coord.
//     glm::vec3 tangent;   // [not used] tangent
//     glm::vec3 bitangent; // [not used] bitangent

//     int   m_BoneIDs[MAX_BONE_INFLUENCE]; // bone indexes which will influence this vertex
//     float m_Weights[MAX_BONE_INFLUENCE]; // weights from each bone
// } Vertex;

Mesh GetBoxMesh() {
    // return a 3d box.
    std::vector<Vertex> vertices = {
        Vertex{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{+0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{+0.5f, +0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{+0.5f, +0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{-0.5f, +0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //

        Vertex{{-0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{+0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{+0.5f, +0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{+0.5f, +0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{-0.5f, +0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{-0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //

        Vertex{{-0.5f, +0.5f, +0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{-0.5f, +0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{-0.5f, -0.5f, +0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{-0.5f, +0.5f, +0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //

        Vertex{{0.5f, +0.5f, +0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{0.5f, +0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{0.5f, -0.5f, +0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{0.5f, +0.5f, +0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //

        Vertex{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{+0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{+0.5f, -0.5f, +0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{+0.5f, -0.5f, +0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{-0.5f, -0.5f, +0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //

        Vertex{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{+0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{+0.5f, 0.5f, +0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{+0.5f, 0.5f, +0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{-0.5f, 0.5f, +0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, //
        Vertex{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}  //
    };
    std::vector<GLuint> indices = {};
    for (size_t i = 0; i < vertices.size(); i++) {
        indices.push_back(i);
    }
    std::vector<Texture> textures;
    Texture              text = Texture("gESgL.jpeg", APP_RESOURCES_PATH "/images");
    textures.push_back(text);

    return Mesh(vertices, indices, textures);
}

Mesh GetPlaneMesh(int axis) {
    // 0: x axis.
    // 1: y axis.
    // 2: z axis.
    std::vector<Vertex> vertices = {
        Vertex{{+0.5, -0.5, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // 0
        Vertex{{+0.5, +0.5, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // 1
        Vertex{{-0.5, +0.5, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // 2
        Vertex{{+0.5, -0.5, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // 3
        Vertex{{-0.5, +0.5, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // 4
        Vertex{{-0.5, -0.5, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}  // 5
    };
    std::vector<GLuint> indices = {
        0, 1, 2, // first
        3, 4, 5  // second
    };
    if (axis == 0) {
        for (size_t i = 0; i < vertices.size(); i++) {
            float temp         = vertices[i].pos.x;
            vertices[i].pos.x  = vertices[i].pos.z;
            vertices[i].pos.z  = temp;
            vertices[i].normal = glm::vec3(1.0f, 0.0f, 0.0f);
        }
    } else if (axis == 1) {
        for (size_t i = 0; i < vertices.size(); i++) {
            float temp         = vertices[i].pos.y;
            vertices[i].pos.y  = vertices[i].pos.z;
            vertices[i].pos.z  = temp;
            vertices[i].normal = glm::vec3(0.0f, 1.0f, 0.0f);
        }
    }
    std::vector<Texture> textures;
    return Mesh(vertices, indices, textures);
}

Mesh GetPyramidMesh() {
    // get Mesh of Pyramid.
    std::vector<Vertex> vertices = {
        Vertex{{-0.5f, +0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // left up
        Vertex{{+0.5f, +0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // right up
        Vertex{{+0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // right down

        Vertex{{-0.5f, +0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // left up
        Vertex{{+0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // right down
        Vertex{{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // left down

        Vertex{{-0.5f, +0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // left up
        Vertex{{+0.5f, +0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // right up
        Vertex{{+0.0f, +0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // top croner

        Vertex{{+0.5f, +0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // right up
        Vertex{{+0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // right down
        Vertex{{+0.0f, +0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // top croner

        Vertex{{+0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // right down
        Vertex{{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // left down
        Vertex{{+0.0f, +0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // top croner

        Vertex{{-0.5f, +0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // left up
        Vertex{{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}, // left down
        Vertex{{+0.0f, +0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.0f, 0.0f, 0.0f}}  // top croner
    };
    std::vector<GLuint> indices = {
        0, 1, 2,    // bottom
        3, 4, 5,    // bottom
        6, 7, 8,    // back
        9, 10, 11,  // right
        12, 13, 14, // front
        15, 16, 17  // left
    };
    std::vector<Texture> textures;
    return Mesh(vertices, indices, textures);
}