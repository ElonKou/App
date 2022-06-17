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

void RayTracingDemo::InitApp() {
    m_viewport = std::make_shared<MainViewport>();
    cam        = std::make_shared<RayTracingCamera>();
    img        = std::make_shared<SimpleImage>();
    core       = std::make_shared<RayTracingCore>();
    cont       = std::make_shared<RayTracingControlWindow>();
    disp       = std::make_shared<RayTracingWindow>();

    scene   = std::make_shared<RayTracingScene>();
    sphere1 = std::make_shared<RaySphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
    sphere2 = std::make_shared<RaySphere>(glm::vec3(0.0f, 100.5f, -1.0f), 100.0f);
    scene->AddObject(sphere1);
    scene->AddObject(sphere2);

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