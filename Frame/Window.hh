#pragma once

#include "Base.hh"
#include "Camera.hh"

class Window {
  public:
    GLFWwindow* window;      // window pointer.
    std::string window_name; // window name.
    int         width;       // window width.
    int         height;      // window height.

    Window();

    ~Window();

    bool Closed();                    // whether window should be closed.
    void PollEvents();                // check all events and use callback functions.
    void Swap();                      // swap buffers.
    void SetInterval(int frame_rate); // set internale time.
    void Clear();                     // use clear color clear window.
    void Terminate();                 // terminate window/
    void CloseMouse();                // Close mouse display.

    void MouseCallbackFunc(GLFWwindow* window, int button, int action, int mode);

    void MousePosCallbackFunc(GLFWwindow* window, double x, double y);

    void KeyboardCallbackFunc(GLFWwindow* window, int key, int scan, int action, int mode);

    void ResizeWindowCallbackFunc(GLFWwindow* window, int w, int h);

    void ScrollCallbackFunc(GLFWwindow* window, double x, double y);
};
