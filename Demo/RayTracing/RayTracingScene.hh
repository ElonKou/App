#pragma once

#include "RayObject.hh"

class RayTracingScene {
  public:
    RayTracingScene() {}

    ~RayTracingScene() {}

    void AddObject(std::shared_ptr<RayObject> obj) {
        objects.push_back(obj);
    }

    bool Hit(Ray& r, float t_min, float t_max, RayHitRecord& rec);

  public:
    std::vector<std::shared_ptr<RayObject>> objects;
};
