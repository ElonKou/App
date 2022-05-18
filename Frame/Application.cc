/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : Application.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Sun May 15 11:32:39 2022
================================================================*/

#include "Application.hh"
#include <iostream>

Application::Application() {}

Application::~Application() {
    TerminateApp();
    std::cout << "destructor Application" << std::endl;
}

void Application::CloseMouse() {
    if (m_viewport) {
        glfwSetInputMode(m_viewport->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

void Application::KeyCallbackFunc(GLFWwindow* window, int key, int scanmode, int key_action, int mode) {
    if (key == GLFW_KEY_ESCAPE && key_action == GLFW_PRESS) {
        m_viewport->isrunning = false;
    }
}

void Application::MouseCallbackFunc(GLFWwindow* window, int bt, int action, int mode) {
    if (bt == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // std::cout << bt << " " << action << " " << mode << std::endl;
    }
}

void Application::ScrollCallback(GLFWwindow* window, double x, double y) {
    // std::cout << x << " " << y << std::endl;
}

void Application::MousePositionCallback(GLFWwindow* window, double x, double y) {
    // std::cout << x << " " << y << std::endl;
}

void Application::RunApp() {
    if (m_viewport) {
        m_viewport->StartWindow(*this);
    }
}

void Application::TerminateApp() {
}