#pragma once

#include "RayMaterial.hh"

class RayMetal : public RayMaterial {
  public:
    RayMetal() {}

    RayMetal(glm::vec3 color, float f)
        : albedo(color)
        , fuzz(f < 1.0f ? f : 1.0f) {}

    ~RayMetal() {}

    virtual bool Scatter(const Ray& rin, const RayHitRecord& rec, glm::vec3& attenuation, Ray& scattered) override {
        glm::vec3 reflacted = Reflect(glm::normalize(rin.dir), rec.normal);
        // scattered           = Ray(rec.pos, reflacted);
        scattered   = Ray(rec.pos, reflacted + fuzz * GetRandomVector(false));
        attenuation = albedo;
        return (glm::dot(reflacted, rec.normal) > 0); // whethere reflacted ray is the opposite direction with record normal.
    }

  public:
    glm::vec3 albedo;
    float     fuzz;
};
