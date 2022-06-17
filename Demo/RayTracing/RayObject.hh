#pragma once

#include "Ray.hh"

typedef struct RayHitRecord {
    glm::vec3 pos;    // position of hit point.
    glm::vec3 normal; // normal of hit point.
    float     t;      // ray variable for calculate distance vector.
    bool      front;  // whether this is front face of the ray.

    inline void SetFaceNormal(Ray& r, glm::vec3& out_normal) {
        // check normal direction
        // we decide to have the normals always point against the ray.
        front  = glm::dot(r.dir, normal) < 0.0f;
        normal = front ? out_normal : -1.0f * out_normal;
    }
} RayHitRecord;

class RayObject {
  public:
    RayObject() {}

    virtual ~RayObject() {}

    virtual bool Hit(Ray& r, float t_min, float t_max, RayHitRecord& rec) = 0;
};
