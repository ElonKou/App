/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : RayTracingCore.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Thu Jun 16 11:08:16 2022
================================================================*/

#include "RayTracingCore.hh"

glm::vec3 RayTracingCore::GetPixelColor(Ray& r, std::shared_ptr<RayTracingScene> scene_, int depth) {
    // glm::vec3 sphere_pos    = glm::vec3(0.0f, 0.0f, -1.0f);
    // float     sphere_radius = 0.5f;
    // float     t             = HitShpere(sphere_pos, sphere_radius, r);
    // if (t > 0.0f) {
    //     glm::vec3 N = glm::normalize(r.at(t) - sphere_pos);
    //     return 0.5f * N + glm::vec3(0.5f);
    // }

    if (depth <= 0) {
        return glm::vec3(0.0f);
    }

    RayHitRecord rec;
    if (scene_->Hit(r, 0.001f, 1e10, rec)) {
        Ray       scattered;
        glm::vec3 attenuation;
        if (rec.mat->Scatter(r, rec, attenuation, scattered))
            return attenuation * GetPixelColor(scattered, scene_, depth - 1);
        // return (attenuation + GetPixelColor(scattered, scene_, depth - 1)) * 0.5f;
        // return (attenuation * 0.2f + GetPixelColor(scattered, scene_, depth - 1) * 0.8f);
        return glm::vec3(0.0f);

        // glm::vec3 target = rec.pos + rec.normal + GetRandomVector();
        // Ray       nr     = Ray(rec.pos, target - rec.pos);
        // return 0.5f * GetPixelColor(nr, scene_, depth - 1);

        // return 0.5f * rec.normal + glm::vec3(0.5f);
    }

    glm::vec3 unit = glm::normalize(r.dir);
    float     t    = 0.5f * (unit.y + 1.0f);
    return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.4f, 0.6f, 1.0f);
}

void RayTracingCore::ResetCamera() {
    cam = std::make_shared<RayTracingCamera>();
}

void RayTracingCore::Render() {
    if (img) {
        Ray r;
        for (size_t i = 0; i < img->height; i++) {
            for (size_t j = 0; j < img->width; j++) {
                std::cerr << "\rScanlines remaining: " << img->height - i << ' ' << std::flush;
                glm::vec3 color = glm::vec3(0.0f);
                for (size_t k = 0; k < samples; k++) {
                    float u = 1.0f * (j + GetRandomFloat()) / (img->width - 1);
                    float v = 1.0f * (i + GetRandomFloat()) / (img->height - 1);
                    r       = cam->GetRay(u, v);
                    color   = color + GetPixelColor(r, scene, max_depth);
                }
                color   = color / (samples * 1.0f);
                color.x = glm::pow(color.x, 1.0f / gamma); // gamma correct color.
                color.y = glm::pow(color.y, 1.0f / gamma); // gamma correct color.
                color.z = glm::pow(color.z, 1.0f / gamma); // gamma correct color.
                img->SetPixel(j, img->height - 1 - i, color);
            }
        }
        img->UploadImage();
    }
}

void RayTracingCore::ChangeColor() {
    if (img) {
        for (size_t i = 0; i < img->height; i++) {
            for (size_t j = 0; j < img->width; j++) {
                img->SetPixel(j, i, glm::vec3(i * 1.0 / img->height, j * 1.0 / img->width, 0.5));
            }
        }
        img->UploadImage();
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