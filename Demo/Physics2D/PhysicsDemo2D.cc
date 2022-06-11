/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : PhysicsDemo2D.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Thu Jun  9 11:55:09 2022
================================================================*/

#include "PhysicsDemo2D.hh"

PhysicsDemo2D::PhysicsDemo2D() {
}

PhysicsDemo2D::~PhysicsDemo2D() {
}

void PhysicsDemo2D::InitApp() {
    info.title   = "Physics2D demo";
    info.version = "v0.0.1";
    m_viewport   = std::make_shared<MainViewport>(info);

    phy           = std::make_shared<Physics2D>();
    viewer        = std::make_shared<PhysicsViewer2D>();
    scene         = std::make_shared<PhysicsScene2D>();
    viewer->phy   = phy;
    viewer->scene = scene;
    phy->scene    = scene;
}

void PhysicsDemo2D::UpdateApp() {
    static float last_time = glfwGetTime();
    float        now_time  = glfwGetTime();
    if (phy) {
        phy->UpdateObjects(now_time - last_time);
        last_time = now_time;
    }
    if (viewer) {
        viewer->Show();
    }
}