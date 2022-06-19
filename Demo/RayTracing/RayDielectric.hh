#pragma once

#include "RayMaterial.hh"

class RayDielectric : public RayMaterial {
  public:
    RayDielectric() {}

    RayDielectric(float ir_)
        : ir(ir_) {}

    ~RayDielectric() {}

    virtual bool Scatter(const Ray& rin, const RayHitRecord& rec, glm::vec3& attenuation, Ray& scattered) override {
        attenuation         = glm::vec3(1.0f);
        float refract_ratio = rec.front ? (1.0f / ir) : ir;

        glm::vec3 v_in      = glm::normalize(rin.dir);
        float     cos_theta = glm::dot(-1.0f * v_in, rec.normal);
        // cos_theta           = cos_theta > 1.0f ? 1.0f : cos_theta;
        cos_theta       = cos_theta < 1.0f ? cos_theta : 1.0f;
        float sin_theta = sqrt(1.0f - cos_theta * cos_theta);

        bool      only_reflect = (refract_ratio * sin_theta) > 1.0f;
        glm::vec3 dir;

        if (only_reflect || reflectance(cos_theta, refract_ratio) > GetRandomFloat()) {
            dir = Reflect(v_in, rec.normal); // reflect
        } else {
            dir = Refract(v_in, rec.normal, refract_ratio); // reflact.
        }
        scattered = Ray(rec.pos, dir);
        return true;
    }

    static float reflectance(float cosine, float ref_idx) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
        r0      = r0 * r0;
        return r0 + (1.0f - r0) * pow((1.0f - cosine), 5);
    }

  public:
    float ir; // index of refraction.
};
