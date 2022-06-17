/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : RayTracingCore.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Thu Jun 16 11:08:16 2022
================================================================*/

#include "RayTracingCore.hh"

glm::vec3 RayTracingCore::GetColor(Ray& r) {
    // glm::vec3 sphere_pos    = glm::vec3(0.0f, 0.0f, -1.0f);
    // float     sphere_radius = 0.5f;
    // float     t             = HitShpere(sphere_pos, sphere_radius, r);
    // if (t > 0.0f) {
    //     glm::vec3 N = glm::normalize(r.at(t) - sphere_pos);
    //     return 0.5f * N + glm::vec3(0.5f);
    // }

    RayHitRecord rec;
    if (scene->Hit(r, 0, 10e10, rec)) {
        return 0.5f * rec.normal + glm::vec3(0.5f);
    }
    glm::vec2 uv = r.dir + cam->ori - cam->center;
    uv.x         = uv.x / cam->horizontal.x;
    uv.y         = uv.y / cam->vertical.y;
    return glm::vec3(uv, 0.8f);

    // glm::vec3 unit = glm::normalize(r.dir);
    // float     t    = 0.5f * (unit.y + 1.0f);
    // return t * glm::vec3(1.0f, 1.0f, 1.0f) + (1.0f - t) * glm::vec3(0.4f, 0.6f, 1.0f);
}

void RayTracingCore::Render() {
    if (img) {
        for (size_t i = 0; i < img->height; i++) {
            for (size_t j = 0; j < img->width; j++) {
                float     u         = 1.0f * j / (img->width - 1);
                float     v         = 1.0f * i / (img->height - 1);
                glm::vec3 direction = glm::vec3(cam->center + cam->horizontal * u + cam->vertical * v - cam->ori);
                Ray       r         = Ray(cam->ori, direction);
                glm::vec3 c         = GetColor(r);
                img->SetPixel(j, i, c);
            }
        }
        img->Upload();
    }
}

void RayTracingCore::ChangeColor() {
    if (img) {
        for (size_t i = 0; i < img->height; i++) {
            for (size_t j = 0; j < img->width; j++) {
                img->SetPixel(j, i, glm::vec3(i * 1.0 / img->height, j * 1.0 / img->width, 0.5));
            }
        }
        img->Upload();
    }
}

float RayTracingCore::HitShpere(glm::vec3& pos, float& radius, Ray& r) {
    glm::vec3 oc      = r.ori - pos;
    float     a       = glm::dot(r.dir, r.dir);
    float     b       = glm::dot(oc, r.dir);
    float     c       = glm::dot(oc, oc) - radius * radius;
    float     delta_t = b * b - a * c;
    if (delta_t < 0) {
        return -1.0f;
    } else {
        return (-1.0f * b - sqrt(delta_t)) / a;
    }
}