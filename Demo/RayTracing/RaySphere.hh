#pragma once

#include "RayObject.hh"

class RaySphere : public RayObject {
  public:
    RaySphere();

    RaySphere(glm::vec3 pos, float r);

    ~RaySphere();

    virtual bool Hit(Ray& r, float t_min, float t_max, RayHitRecord& rec) override;

  public:
    glm::vec3 center; // center  of sphere.
    float     radius; // radius of this sphere.
};
