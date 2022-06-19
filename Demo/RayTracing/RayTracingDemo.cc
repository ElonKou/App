/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : RayTracingDemo.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Wed Jun 15 20:24:28 2022
================================================================*/

#include "RayTracingDemo.hh"

RayTracingDemo::RayTracingDemo() {
}

RayTracingDemo::~RayTracingDemo() {
}

void CreateScene1(std::shared_ptr<RayTracingScene>& scene) {
    auto material_ground = std::make_shared<RayLambertian>(glm::vec3(0.8f, 0.8f, 0.0f));
    auto material_center = std::make_shared<RayLambertian>(glm::vec3(0.1f, 0.2f, 0.5f));
    // auto material_left   = std::make_shared<RayMetal>(glm::vec3(0.8f, 0.8f, 0.8f), 0.3f);
    // auto material_center = std::make_shared<RayDielectric>(1.5f);
    auto material_left  = std::make_shared<RayDielectric>(1.5f);
    auto material_right = std::make_shared<RayMetal>(glm::vec3(0.8f, 0.6f, 0.2f), 0.0f);

    auto sphere1 = std::make_shared<RaySphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f, material_ground);
    auto sphere2 = std::make_shared<RaySphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, material_center);
    auto sphere3 = std::make_shared<RaySphere>(glm::vec3(-1.0f, 0.0f, -1.0f), 0.5f, material_left);
    auto sphere4 = std::make_shared<RaySphere>(glm::vec3(-1.0f, 0.0f, -1.0f), -0.4f, material_left);
    auto sphere5 = std::make_shared<RaySphere>(glm::vec3(1.0f, 0.0f, -1.0f), 0.5f, material_right);

    scene->AddObject(sphere1);
    scene->AddObject(sphere2);
    scene->AddObject(sphere3);
    scene->AddObject(sphere4);
    scene->AddObject(sphere5);
}

void CreateScene2(std::shared_ptr<RayTracingScene>& scene) {
    float R = cos(glm::pi<float>() / 4.0f);

    auto material_left  = std::make_shared<RayLambertian>(glm::vec3(0.0f, 0.0f, 1.0f));
    auto material_right = std::make_shared<RayLambertian>(glm::vec3(1.0f, 0.0f, 0.0f));

    auto sphere1 = std::make_shared<RaySphere>(glm::vec3(-R, 0.0f, -1.0f), R, material_left);
    auto sphere2 = std::make_shared<RaySphere>(glm::vec3(R, 0.0f, -1.0f), R, material_right);

    scene->AddObject(sphere1);
    scene->AddObject(sphere2);
}
void CreateScene3(std::shared_ptr<RayTracingScene>& scene) {
    auto ground_material = std::make_shared<RayLambertian>(glm::vec3(0.5, 0.5, 0.5));
    auto ground_sphere   = std::make_shared<RaySphere>(glm::vec3(0.0f, -1000.0f, 0.0f), 1000.0f, ground_material);
    scene->AddObject(ground_sphere);

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto      choose_mat = GetRandomFloat();
            glm::vec3 center(a + 0.9 * GetRandomFloat(), 0.2, b + 0.9 * GetRandomFloat());

            if ((center - glm::vec3(4.0f, 0.2f, 0.0f)).length() > 0.9) {
                std::shared_ptr<RayMaterial> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo     = GetRandomVec3() * GetRandomVec3();
                    sphere_material = std::make_shared<RayLambertian>(albedo);
                    auto obj        = std::make_shared<RaySphere>(center, 0.2, sphere_material);
                    scene->AddObject(obj);
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo     = GetRandomVec3();
                    auto fuzz       = GetRandomFloat() * 0.5f;
                    sphere_material = std::make_shared<RayMetal>(albedo, fuzz);
                    auto obj        = std::make_shared<RaySphere>(center, 0.2, sphere_material);
                    scene->AddObject(obj);
                } else {
                    // glass
                    sphere_material = std::make_shared<RayDielectric>(1.5);
                    auto obj        = std::make_shared<RaySphere>(center, 0.2, sphere_material);
                    scene->AddObject(obj);
                }
            }
        }
    }

    auto material1 = std::make_shared<RayDielectric>(1.5);
    auto obj1      = std::make_shared<RaySphere>(glm::vec3(0, 1, 0), 1.0, material1);
    scene->AddObject(obj1);

    auto material2 = std::make_shared<RayLambertian>(glm::vec3(0.4, 0.2, 0.1));
    auto obj2      = std::make_shared<RaySphere>(glm::vec3(-4, 1, 0), 1.0, material2);
    scene->AddObject(obj2);

    auto material3 = std::make_shared<RayMetal>(glm::vec3(0.7, 0.6, 0.5), 0.0);
    auto obj3      = std::make_shared<RaySphere>(glm::vec3(4, 1, 0), 1.0, material3);
    scene->AddObject(obj3);
}

void RayTracingDemo::InitApp() {
    info.title   = "RayTracing";
    info.version = "v0.0.1";
    m_viewport   = std::make_shared<MainViewport>(info);

    // glm::vec3 lookfrom(3, 3, 2);
    // glm::vec3 lookat(0, 0, -1);
    // glm::vec3 vup(0, 1, 0);
    // float     v_fov         = 20.0f;
    // float     dist_to_focus = glm::length(lookfrom - lookat);
    // float     aperture      = 0.2;
    // cam = std::make_shared<RayTracingCamera>(lookfrom, lookat, vup, v_fov, aperture, dist_to_focus);

    glm::vec3 lookfrom(13.0f, 2.0f, 3.0f);
    glm::vec3 lookat(0.0f, 0.0f, 0.0f);
    glm::vec3 vup(0.0f, 1.0f, 0.0f);
    float     dist_to_focus = 10.0f;
    float     aperture      = 0.1f;
    cam                     = std::make_shared<RayTracingCamera>(lookfrom, lookat, vup, 20.0f, aperture, dist_to_focus);
    // cam                     = std::make_shared<RayTracingCamera>();

    img   = std::make_shared<SimpleImage>();
    core  = std::make_shared<RayTracingCore>();
    cont  = std::make_shared<RayTracingControlWindow>();
    disp  = std::make_shared<RayTracingWindow>();
    scene = std::make_shared<RayTracingScene>();

    // CreateScene1(scene);
    // CreateScene2(scene);

    CreateScene3(scene);

    img->GenerateImage(cam->image_width, cam->image_height, 3);

    disp->img   = img;
    core->img   = img;
    core->cam   = cam;
    core->scene = scene;
    cont->core  = core;
}

void RayTracingDemo::UpdateApp() {
    if (disp) {
        disp->Show();
    }
    if (cont) {
        cont->Show();
    }
}