#pragma once

#include "Ray.hh"
#include "RayLambertian.hh"
#include "RayMetal.hh"
#include "RayTracingCamera.hh"
#include "RayTracingScene.hh"
#include "SimpleImage.hh"

class RayTracingCore {
  public:
    RayTracingCore() {
        samples   = 30;
        max_depth = 10;
        gamma     = 2.0f;
    }

    ~RayTracingCore() {}

    glm::vec3 GetPixelColor(Ray& r, std::shared_ptr<RayTracingScene> scene, int depth);

    void ResetCamera();

    void Render();

    void ChangeColor();

    float HitShpere(glm::vec3& pos, float& radius, Ray& r);

  private:
    glm::vec3 GetRandomVector() {
        while (true) {
            glm::vec3 p = glm::vec3(GetRandomFloat() * 2.0f - 1.0f, GetRandomFloat() * 2.0f - 1.0f, GetRandomFloat() * 2.0f - 1.0f);
            if (glm::length(p) >= 1.0f) {
                continue;
            }
            return glm::normalize(p);
        }
    }

  public:
    std::shared_ptr<RayTracingCamera> cam;
    std::shared_ptr<SimpleImage>      img;
    std::shared_ptr<RayTracingScene>  scene;

    int   samples;   // samples number.
    int   max_depth; // diffuse material depth.
    float gamma;     //gamma for correct color.
};
