/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : RaySphere.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Thu Jun 16 22:31:02 2022
================================================================*/

#include "RaySphere.hh"
RaySphere::RaySphere() {}

RaySphere::RaySphere(glm::vec3 pos, float r, std::shared_ptr<RayMaterial> m)
    : center(pos)
    , radius(r)
    , mat(m) {
}

RaySphere::~RaySphere() {}

bool RaySphere::Hit(Ray& r, float t_min, float t_max, RayHitRecord& rec) {
    glm::vec3 oc      = r.ori - center;
    float     a       = glm::dot(r.dir, r.dir);
    float     b       = glm::dot(oc, r.dir);
    float     c       = glm::dot(oc, oc) - radius * radius;
    float     delta_t = b * b - a * c;
    if (delta_t < 0) {
        return false;
    } else {
        float root = (-1.0f * b - sqrt(delta_t)) / a;
        if (root < t_min || root > t_max) {
            root = (-1.0f * b + sqrt(delta_t)) / a;
            if (root < t_min || root > t_max) {
                return false;
            }
        }
        rec.t      = root;
        rec.pos    = r.at(rec.t);
        rec.mat    = mat;
        rec.normal = (rec.pos - center) / radius;
        rec.SetFaceNormal(r, rec.normal);
        return true;
    }
}