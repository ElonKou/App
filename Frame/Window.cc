/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : Window.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Sun 19 Apr 2020 01:09:18 PM CST
================================================================*/

#include "Window.hh"

Window::Window() {
    window_name = APP_VERSION "@elonkou";
    width       = 800;
    height      = 600;

    glfwInit();
#ifdef __APPLE__
    // GL 3.2 + GLSL 150
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
    glfwWindowHint(GLFW_SAMPLES, 4);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    // glfwWindowHint(GLFW_SAMPLES, 4);
    // glEnable(GL_MULTISAMPLE);
    // glDisable(GL_MULTISAMPLE);

    // for moving the window into center of monior.
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
#endif

    window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
    if (!window) {
        std::cout << "Error create window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // use static_cast to convert member function to
    // auto mouse_func = [](GLFWwindow* w, int button, int action, int mode) {
    //     static_cast<Window*>(glfwGetWindowUserPointer(w))->MouseCallbackFunc(w, button, action, mode);
    //     cam.mouse_click_callback(w, button, action, mode);
    // };
    // auto mouse_pos_func = [](GLFWwindow* w, double x, double y) {
    //     static_cast<Window*>(glfwGetWindowUserPointer(w))->MousePosCallbackFunc(w, x, y);
    //     cam.mouse_move_callback(w, x, y);
    // };
    // auto key_func = [](GLFWwindow* w, int key, int scan, int action, int mode) {
    //     static_cast<Window*>(glfwGetWindowUserPointer(w))->KeyboardCallbackFunc(w, key, scan, action, mode);
    // };
    // auto resize_func = [](GLFWwindow* w, int width, int height) {
    //     static_cast<Window*>(glfwGetWindowUserPointer(w))->ResizeWindowCallbackFunc(w, width, height);
    //     cam.cam_width  = width;
    //     cam.cam_height = height;
    // };
    // auto scroll_func = [](GLFWwindow* w, double x, double y) {
    //     static_cast<Window*>(glfwGetWindowUserPointer(w))->ScrollCallbackFunc(w, x, y);
    //     cam.scroll_callback(w, x, y);
    // };

    // glfwSetMouseButtonCallback(window, mouse_func);
    // glfwSetCursorPosCallback(window, mouse_pos_func);
    // glfwSetKeyCallback(window, key_func);
    // glfwSetFramebufferSizeCallback(window, resize_func);
    // glfwSetScrollCallback(window, scroll_func);

    glewInit(); // init before use openGL.
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);
    // cam.cam_width  = width;
    // cam.cam_height = height;

    std::cout << "Window size : " << width << " " << height << std::endl;

    // move window to center
#ifdef __unix__
    int                count; // moniter count
    GLFWmonitor**      monitors     = glfwGetMonitors(&count);
    const GLFWvidmode* videoMode    = glfwGetVideoMode(monitors[0]);
    int                windowWidth  = (videoMode->width - width) / 2;
    int                windowHeight = (videoMode->height - height) / 2;
    glfwDefaultWindowHints();
    glfwSetWindowPos(window, windowWidth, windowHeight);
    glfwShowWindow(window);
#endif

    glEnable(GL_DEPTH_TEST);
}

Window::~Window() {
}

bool Window::Closed() {
    return glfwWindowShouldClose(window);
}

void Window::PollEvents() {
    glfwPollEvents();
}

void Window::Swap() {
    glfwSwapBuffers(window);
}

void Window::SetInterval(int frame_rate) {
    glfwSwapInterval(frame_rate);
}

void Window::Clear() {
    glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::Terminate() {
    glfwTerminate();
}

// --------------------------------------------------Callback functions----------------------------------------------------------------
void Window::MouseCallbackFunc(GLFWwindow* window, int button, int action, int mode) {
    // std::cout << "button: " << button << " acction: " << action << " mode: " << mode << std::endl;
}

void Window::MousePosCallbackFunc(GLFWwindow* window, double x, double y) {
    // std::cout << "mouse pos : (" << x << ", " << y << ")" << std::endl;
}

void Window::KeyboardCallbackFunc(GLFWwindow* window, int key, int scan, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        // std::cout << "key: " << key << " scan: " << scan << " acction: " << action << " mode: " << mode << std::endl;
        glfwSetWindowShouldClose(window, true);
    }
}

void Window::ResizeWindowCallbackFunc(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, w, h);
}

void Window::ScrollCallbackFunc(GLFWwindow* window, double x, double y) {
    // std::cout <<  "scroll (" << x << ", " << y << ")" << std::endl;
}
// --------------------------------------------------Callback functions----------------------------------------------------------------
