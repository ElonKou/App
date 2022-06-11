/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : AppDemo.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Tue May 17 19:14:48 2022
================================================================*/

#include "AppDemo.hh"

void AppDemo::MousePositionCallback(GLFWwindow* window, double x, double y) {
    // std::cout << x << " " << y << std::endl;
}

void AppDemo::InitApp() {
    info.title  = "SomeAppDemo";
    info.author = "elonkou";
    m_viewport  = std::make_shared<MainViewport>(info);
    menu        = std::make_shared<Menu>();
    cwin        = std::make_shared<ControlWindow>();
    dwin        = std::make_shared<DisplyWindow>();
}

void AppDemo::UpdateApp() {
    if (menu) {
        menu->Show();
    }
    if (cwin) {
        cwin->Show();
    }
    if (dwin) {
        dwin->Show();
    }
}
