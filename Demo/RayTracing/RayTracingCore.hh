#pragma once

#include "Ray.hh"
#include "RayTracingCamera.hh"
#include "RayTracingScene.hh"
#include "SimpleImage.hh"
#include <climits>

class RayTracingCore {
  public:
    std::shared_ptr<RayTracingCamera> cam;
    std::shared_ptr<SimpleImage>      img;
    std::shared_ptr<RayTracingScene>  scene;

    RayTracingCore() {}

    ~RayTracingCore() {}

    glm::vec3 GetColor(Ray& r);

    void Render();

    void ChangeColor();

    float HitShpere(glm::vec3& pos, float& radius, Ray& r);
};
