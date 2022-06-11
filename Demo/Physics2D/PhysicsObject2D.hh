#pragma once

#include "Base.hh"

class PhysicsObject2D {
  public:
    glm::vec2 old_pos;       // old position.
    glm::vec2 pos;           // current position.
    glm::vec2 accerleration; // accerleration of current object.
    bool      fixed;         // whether this is an static object.

    PhysicsObject2D() {
        accerleration = old_pos = pos = glm::vec2(0.0f);
        fixed                         = false;
    }

    virtual ~PhysicsObject2D() {}

    void SetVelocity(glm::vec2 acc) {
        accerleration = acc;
    }

    virtual void Init() = 0;
};

class Circle : public PhysicsObject2D {
  public:
    glm::vec4 col;    // color.
    float     radius; // radius.

    Circle() {}

    ~Circle() {}

    void Init();
};