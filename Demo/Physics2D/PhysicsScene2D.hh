#pragma once

#include "PhysicsLink2D.hh"
#include "PhysicsObject2D.hh"

class PhysicsScene2D {
  public:
    std::vector<Circle>        objects; // All objects.
    std::vector<PhysicsLink2D> links;   // all links.
    glm::vec2                  gravity; // gravity.
    size_t                     obj_cnt;
    size_t                     link_cnt;

    PhysicsScene2D();

    ~PhysicsScene2D();

    void AddObject(glm::vec2 pos, glm::vec2 acc = glm::vec2(0.0f));

    void AddLink(size_t na, size_t nb, float dist);

  private:
    void BuildScene();
};
