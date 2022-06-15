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
    img        = std::make_shared<SimpleImage>();
    img->GenerateImage(800, 600, 3);

    cont = std::make_shared<RayTracingControlWindow>();
    disp = std::make_shared<RayTracingWindow>();

    disp->img = img;
    cont->img = img;
}

void RayTracingDemo::UpdateApp() {
    if (disp) {
        disp->Show();
    }
    if (cont) {
        cont->Show();
    }
}