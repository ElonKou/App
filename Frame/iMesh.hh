#pragma once

#include "Base.hh"
#include "Buffer.hh"
#include "Shader.hh"
#include "Texture.hh"

// TODO
class iMesh {
  public:
    std::vector<GLfloat> vertices;  // all vertex point.
    std::vector<GLuint>  indices;   // all index.
    std::vector<GLint>   format;    // format for shader read.

    glm::vec3 pos;      // position of iMesh object.
    glm::vec3 scale;    // scale the iMesh Object.
    glm::vec3 rotation; // rotation angle.

    Buffer   buffer;
    Texture* texture;
    Shader*  shader;

    iMesh();

    iMesh(float radius);

    ~iMesh();

    glm::mat4 GetModelMatrix();

    void Init();

    void Draw();
};

class Triangle {
  public:
    Triangle() {}

    ~Triangle() {}
};

iMesh GetTriangle(float radius = 0.8, bool color = false, bool texture = false);
iMesh GetRect(float radius = 0.5);
iMesh GetRectWithCoord();
iMesh GetRectWithTexture(float radius = 0.5);
iMesh GetRectWithoutColor(float radius = 0.5);
iMesh GetSphere2D(float radius = 0.5, int cnt = 24);
iMesh GetSphere3D(float radius = 0.5, int cnt = 24);
iMesh GetHeart(int cnt = 24);

// 3D
iMesh GetBox(float radius = 0.5);
iMesh GetMiddleBox(float radius = 0.5);
iMesh GetSimpleBox(float radius = 0.5);
iMesh GetPyramid();
iMesh GetPlane3D(int zero_id = 2);

std::ostream& operator<<(std::ostream& os, glm::mat4& m);
std::ostream& operator<<(std::ostream& os, glm::vec3& v);
std::ostream& operator<<(std::ostream& os, glm::vec4& v);
std::ostream& operator<<(std::ostream& os, glm::quat& q);