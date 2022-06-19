#pragma once

#include "RayMaterial.hh"

class RayLambertian : public RayMaterial {
  public:
    RayLambertian() {}

    RayLambertian(glm::vec3 color)
        : albedo(color) {}

    ~RayLambertian() {}

    virtual bool Scatter(const Ray& rin, const RayHitRecord& rec, glm::vec3& attenuation, Ray& scattered) override {
        glm::vec3 v = GetRandomVector();
        while (NearZero(rec.normal + v)) {
            v = GetRandomVector();
        }
        glm::vec3 scatter_direction = rec.normal + v;
        scattered                   = Ray(rec.pos, scatter_direction);
        attenuation                 = albedo;
        return true;
    };

  public:
    glm::vec3 albedo; // reflact ratio (maybe).
};
