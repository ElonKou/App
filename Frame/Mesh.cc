/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : Mesh.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Thu Feb  3 00:49:21 2022
================================================================*/

#include "Mesh.hh"

Mesh::Mesh() {
    pos      = glm::vec3(0.0f);
    scale    = glm::vec3(1.0);
    rotation = glm::vec3(0.0, 0.0, 0.0); // [Eular] default rotation.
    texture  = nullptr;
    shader   = nullptr;
}

Mesh::Mesh(float radius_) {
    pos      = glm::vec3(0.0f);
    scale    = glm::vec3(1.0);
    rotation = glm::vec3(0.0, 0.0, 0.0); // [Eular] default rotation.
    texture  = nullptr;
    shader   = nullptr;
}

Mesh::~Mesh() {
}

void Mesh::Init() {
    buffer.Init();
    buffer.BindBufferPointer(vertices, indices, format);
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

void Mesh::Draw() {
    buffer.Bind();
    buffer.Draw();
    buffer.UnBind();
}

// ------------------------------------------------------------------------
Mesh GetTriangle(float radius, bool color, bool texture) {
    Mesh ret;
    ret.withcolor = true;
    ret.vertices  = {
        radius, -radius, 0.0f, 1.0f, 0.0f, 0.0f,  // right-down
        -radius, -radius, 0.0f, 0.0f, 1.0f, 0.0f, // left-down
        0.0f, radius, 0.0f, 0.0f, 0.0f, 1.0f      // mid-up
    };
    ret.indices = {0, 1, 2};
    ret.format  = {3, 3};
    return ret;
}

Mesh GetRect(float radius) {
    Mesh ret;
    ret.withcolor = true;
    ret.vertices  = {
        radius, -radius, 0.0f, 1.0f, 0.0f, 0.0f,  // 2
        radius, radius, 0.0f, 0.0f, 1.0f, 0.0f,   // 1
        -radius, radius, 0.0f, 0.0f, 0.0f, 1.0f,  // 0
        -radius, -radius, 0.0f, 1.0f, 1.0f, 0.0f, // 3
        radius, -radius, 0.0f, 0.0f, 1.0f, 1.0f,  // 5
        -radius, radius, 0.0f, 1.0f, 0.0f, 1.0f   // 4
    };
    ret.indices = {
        0, 1, 2, // first
        0, 2, 3  // second
    };
    ret.format = {3, 3};
    return ret;
}

Mesh GetRectWithCoord() {
    Mesh ret;
    ret.withcolor = true;
    ret.withtext  = true;
    ret.vertices  = {
        0.5, -0.5, 0.0f, 1.0f, 0.0f, // 2
        0.5, 0.5, 0.0f, 1.0f, 1.0f,  // 1
        -0.5, 0.5, 0.0f, 0.0f, 1.0f, // 0
        -0.5, -0.5, 0.0f, 0.0f, 0.0f // 3
    };
    ret.indices = {
        0, 1, 2, // first
        0, 2, 3  // second
    };
    ret.format = {3, 2};
    return ret;
}

Mesh GetRectWithTexture(float radius) {
    Mesh ret;
    ret.withcolor = true;
    ret.withtext  = true;
    ret.vertices  = {
        radius, -radius, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 2
        radius, radius, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  // 1
        -radius, radius, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // 0
        -radius, -radius, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f // 3
    };
    ret.indices = {
        0, 1, 2, // first
        0, 2, 3  // second
    };
    ret.format = {3, 3, 2};
    return ret;
}

Mesh GetRectWithoutColor(float radius) {
    Mesh ret;
    ret.withcolor = false;
    ret.vertices  = {
        radius, -radius, 0.0f,  // 2
        radius, radius, 0.0f,   // 1
        -radius, radius, 0.0f,  // 0
        -radius, -radius, 0.0f, // 3
        radius, -radius, 0.0f,  // 5
        -radius, radius, 0.0f   // 4
    };
    ret.indices = {
        0, 1, 2, // first
        0, 2, 3  // second
    };
    ret.format = {3};
    return ret;
}

Mesh GetSphere2D(float radius, int cnt) {
    Mesh ret;
    for (int i = 0; i < cnt; i++) {
    }
    return ret;
}

Mesh GetSphere3D(float radius, int cnt) {
    Mesh ret;
    return ret;
}

Mesh GetHeart(int cnt) {
    // r = a(1 - sin theta)
    Mesh ret;
    ret.withcolor = true;
    float pi      = 3.141582653;
    float a       = 0.5;
    for (int i = 0; i < cnt + 1; i++) {
        float ang = 2 * pi / cnt * i;
        ang       = ang + 0.5 * pi;
        float r   = a * (1 - sin(ang));
        float x   = r * cos(ang) * 0.8;    // center
        float y   = r * sin(ang) + 0.35;   // scale
        x         = x * cos(abs(r - 0.2)); // scale
        // add points for triangle.
        ret.vertices.push_back(x);
        ret.vertices.push_back(y);
        ret.vertices.push_back(0.0);
        // add color of points.
        {
            ang     = ang - 0.5 * pi;
            float r = cos(0.2 * abs(ang - 3.0 / 6 * pi));
            float g = cos(1.0 * abs(ang - 7.0 / 6 * pi));
            float b = cos(1.0 * abs(ang - 11.0 / 6 * pi));
            ret.vertices.push_back(r);
            ret.vertices.push_back(g);
            ret.vertices.push_back(b);
        }
        // add index for triangle.
        ret.indices.push_back(0);
        ret.indices.push_back(i + 1);
        ret.indices.push_back(i + 2);
    }
    ret.format = {3, 3};
    return ret;
}

Mesh GetBox(float radius) {
    // return a 3d box.
    Mesh ret;
    ret.withcolor = false;
    ret.withtext  = true;
    ret.vertices  = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  //
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  //
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, //
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  //
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   //
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   //
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  //
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, //

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  //
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  //
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   //
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   //
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, //
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  //
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,  //
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f  //
    };
    ret.indices = {};
    ret.format  = {3, 2};
    return ret;
}

Mesh GetMiddleBox(float radius) {
    // return a 3d box.
    //                       z
    //   4/-------/5  |      |
    //   /|      /|   |      |
    // 7/-|-----/6|   |      o-------y
    //  | /0----|-/1  |     /
    //  |/      |/    |    /
    // 3/-------/2    |   x
    Mesh ret;
    ret.withcolor = false;
    ret.withtext  = true;
    ret.vertices  = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // back
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  //
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  //

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // front
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  //
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   //
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  //

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // left
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  //
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  //
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   //
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  //
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f   //
    };
    ret.indices = {
        0, 1, 2,    // back
        3, 0, 2,    // back
        4, 5, 6,    // front
        7, 4, 6,    // front
        8, 9, 10,   // left
        11, 8, 10,  // left
        12, 13, 14, // right
        15, 12, 14, // right
        16, 17, 18, // botton
        19, 16, 18, // botton
        20, 21, 22, // top
        23, 20, 22  // top
    };
    ret.format = {3, 2};
    return ret;
}

Mesh GetSimpleBox(float radius) {
    // return a 3d box.
    //                       z
    //   4/-------/5  |      |
    //   /|      /|   |      |
    // 7/-|-----/6|   |      o-------y
    //  | /0----|-/1  |     /
    //  |/      |/    |    /
    // 3/-------/2    |   x
    Mesh ret;
    ret.withcolor = false;
    ret.withtext  = true;
    ret.vertices  = {
        -0.5, -0.5, -0.5, 0.0, 0.0, // 0
        -0.5, 0.5, -0.5, 0.0, 1.0,  // 1
        0.5, 0.5, -0.5, 1.0, 1.0,   // 2
        0.5, -0.5, -0.5, 1.0, 0.0,  // 3

        -0.5, -0.5, 0.5, 1.0, 1.0, // 4
        -0.5, 0.5, 0.5, 1.0, 0.0,  // 5
        0.5, 0.5, 0.5, 0.0, 0.0,   // 6
        0.5, -0.5, 0.5, 0.0, 1.0   // 7
    };
    ret.indices = {
        1, 2, 0, // botton
        2, 3, 0, // botton
        1, 2, 5, // right
        2, 6, 5, // right
        0, 1, 5, // back
        0, 4, 5, // back
        0, 3, 4, // left
        7, 3, 4, // left
        2, 3, 6, // front
        7, 3, 6, // front
        6, 5, 7, // top
        4, 5, 7  // top
    };
    ret.format = {3, 2};
    return ret;
}

Mesh GetPyramid() {
    // get Mesh of Pyramid.
    Mesh ret;
    ret.withcolor = false;
    ret.withtext  = true;
    ret.vertices  = {
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // left up
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // right up
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // right down
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // left down
        0.0f, 0.0f, 1.0f, 0.5f, 0.5f    //  top croner
    };
    ret.indices = {
        0, 1, 2, // bottom
        0, 2, 3, // bottom
        0, 1, 4, // back
        1, 2, 4, // right
        2, 3, 4, // front
        0, 3, 4  // left
    };
    ret.format = {3, 2};
    return ret;
}

Mesh GetPlane3D(int zero_id) {
    Mesh ret;
    ret.withcolor = true;
    ret.withtext  = true;
    ret.vertices  = {
        0.5, -0.5, 0.0f, 1.0f, 0.0f, // 2
        0.5, 0.5, 0.0f, 1.0f, 1.0f,  // 1
        -0.5, 0.5, 0.0f, 0.0f, 1.0f, // 0
        -0.5, -0.5, 0.0f, 0.0f, 0.0f // 3
    };
    ret.indices = {
        0, 1, 2, // first
        0, 2, 3  // second
    };
    ret.format = {3, 2};
    if (zero_id == 0) {
        for (size_t i = 0; i < ret.vertices.size() / 5; i++) {
            float temp              = ret.vertices[5 * i + 0];
            ret.vertices[5 * i + 0] = ret.vertices[5 * i + 2];
            ret.vertices[5 * i + 2] = temp;
        }
    } else if (zero_id == 1) {
        for (size_t i = 0; i < ret.vertices.size() / 5; i++) {
            float temp              = ret.vertices[5 * i + 1];
            ret.vertices[5 * i + 1] = ret.vertices[5 * i + 2];
            ret.vertices[5 * i + 2] = temp;
        }
    }
    return ret;
}

std::ostream& operator<<(std::ostream& os, glm::mat4& m) {
    for (size_t j = 0; j < 4; j++) {
        for (size_t i = 0; i < 4; i++) {
            os << m[j][i] << " ";
        }
        if (j != 3) {
            os << std::endl;
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, glm::vec3& v) {
    for (size_t i = 0; i < 3; i++) {
        os << v[i] << " ";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, glm::vec4& v) {
    for (size_t i = 0; i < 4; i++) {
        os << v[i] << " ";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, glm::quat& q) {
    os << q.w << " " << q.x << " " << q.y << " " << q.z;
    return os;
}