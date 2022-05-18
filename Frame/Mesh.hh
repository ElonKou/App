#pragma once

#include "Base.hh"
#include "Buffer.hh"
#include "Shader.hh"
#include "Texture.hh"

typedef struct Vertex {
    glm::vec3 pos;    // point of vertex.
    glm::vec3 color;  // color of vertex.
    glm::vec3 normal; // color of vertex.
    glm::vec2 coord;  // texture coord.
} Vertex;

// TODO
class Mesh {
  public:
    bool                 withcolor; // whether with vertex color.
    bool                 withtext;  // whether with texture coord.
    std::vector<GLfloat> vertices;  // all vertex point.
    std::vector<GLuint>  indices;   // all index.
    std::vector<GLint>   format;    // format for shader read.

    glm::vec3 pos;         // position of Mesh object.
    glm::vec3 scale;       // scale the Mesh Object.
    glm::vec3 rotation;    // rotation angle.

    Buffer   buffer;
    Texture* texture;
    Shader*  shader;

    Mesh();

    Mesh(float radius);

    ~Mesh();

    glm::mat4 GetModelMatrix();

    void Init();

    void Draw();
};

class Triangle {
  public:
    Triangle() {}

    ~Triangle() {}
};

Mesh GetTriangle(float radius = 0.8, bool color = false, bool texture = false);
Mesh GetRect(float radius = 0.5);
Mesh GetRectWithCoord();
Mesh GetRectWithTexture(float radius = 0.5);
Mesh GetRectWithoutColor(float radius = 0.5);
Mesh GetSphere2D(float radius = 0.5, int cnt = 24);
Mesh GetSphere3D(float radius = 0.5, int cnt = 24);
Mesh GetHeart(int cnt = 24);

// 3D
Mesh GetBox(float radius = 0.5);
Mesh GetMiddleBox(float radius = 0.5);
Mesh GetSimpleBox(float radius = 0.5);
Mesh GetPyramid();
Mesh GetPlane3D(int zero_id = 2);

std::ostream& operator<<(std::ostream& os, glm::mat4& m);
std::ostream& operator<<(std::ostream& os, glm::vec3& v);
std::ostream& operator<<(std::ostream& os, glm::vec4& v);
std::ostream& operator<<(std::ostream& os, glm::quat& q);