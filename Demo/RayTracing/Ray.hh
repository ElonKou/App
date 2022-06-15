#pragma once

#include "Base.hh"

class Ray {
  public:
    Ray() {}

    Ray(const glm::vec3& origin_, const glm::vec3& direction_)
        : ori(origin_)
        , dir(direction_) {}

    ~Ray() {}

    glm::vec3 at(float t) {
        return ori + t * dir;
    }

  public:
    glm::vec3 ori;
    glm::vec3 dir;
};
