#pragma once

#include "RayHitRecord.hh"

class RayObject {
  public:
    RayObject() {}

    virtual ~RayObject() {}

    virtual bool Hit(Ray& r, float t_min, float t_max, RayHitRecord& rec) = 0;
};
