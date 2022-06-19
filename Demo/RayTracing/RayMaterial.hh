#pragma once

#include "RayHitRecord.hh"

class RayMaterial {
  public:
    RayMaterial() {}

    virtual ~RayMaterial() {}

    // according hit record calculate scattered ray.
    // rin : ray in
    // rec : hit record.
    // attenuation :
    // scattered : scattered ray.
    virtual bool Scatter(const Ray& rin, const RayHitRecord& rec, glm::vec3& attenuation, Ray& scattered) = 0;
};
