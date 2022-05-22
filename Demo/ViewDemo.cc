/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : ViewDemo.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Thu May 19 01:58:20 2022
================================================================*/

#include "ViewDemo.hh"

void ViewDemo::KeyCallbackFunc(GLFWwindow* window, int key, int scanmode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        // std::cout << "key: " << key << " scan: " << scan << " acction: " << action << " mode: " << mode << std::endl;
        glfwSetWindowShouldClose(window, true);
    }
}

void ViewDemo::MouseCallbackFunc(GLFWwindow* window, int bt, int action, int mode) {
    if (cam) {
        cam->mouse_click_callback(window, bt, action, mode);
    }
}

void ViewDemo::ScrollCallback(GLFWwindow* window, double x, double y) {
    if (cam) {
        cam->scroll_callback(window, x, y);
    }
}

void ViewDemo::MousePositionCallback(GLFWwindow* window, double x, double y) {
    if (cam) {
        cam->mouse_move_callback(window, x, y);
    }
}

void ViewDemo::InitApp() {
    info.title   = "3DViewDemo";
    info.author  = "elonkou";
    info.version = APP_VERSION;

    m_viewport = std::make_shared<MainViewport>(info);
    menu       = std::make_shared<Menu>();
    cwin       = std::make_shared<ControlWindow>();
    dwin       = std::make_shared<DisplyWindow>();
    owin       = std::make_shared<OpenGLWindow>();

    cam        = std::make_shared<Camera>();
    scene      = std::make_shared<Scene>();
    box        = std::make_shared<Mesh>();
    *box.get() = GetBox();
    scene->AddObj(box.get());
    // CloseMouse();
}

void ViewDemo::UpdateApp() {
    if (menu) {
        menu->Show();
    }
    if (cwin) {
        cwin->Show();
    }
    if (dwin) {
        dwin->Show();
    }

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    cam->ProcessInput(m_viewport->window);
    scene->CameraUpdate(*cam.get());

    box->scale      = glm::vec3(0.5);
    box->rotation.x = glfwGetTime();
    box->rotation.y = glfwGetTime();
    box->pos        = position;

    if (owin) {
        owin->SetSceneCamera(scene, cam);
        owin->Show();
    }
}
