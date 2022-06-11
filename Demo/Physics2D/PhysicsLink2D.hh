#pragma once

#include "PhysicsObject2D.hh"

class PhysicsLink2D {
  public:
    size_t node_a; // PhysicsLink2D node a.
    size_t node_b; // PhysicsLink2D node b.
    float  dist;   // diatnce oftwo PhysicsLink2D Nodes;

    PhysicsLink2D();

    ~PhysicsLink2D();

    void ApplyPhysicsLink2D(Circle& na, Circle& nb);
};
