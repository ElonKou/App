#pragma once
#ifndef LAB_HH_
#define LBB_HH_

#include "MainViewport.hh"

class Application {
  public:
    WindowInfo                    info;
    std::shared_ptr<MainViewport> m_viewport;

    Application();

    ~Application();

    void CloseMouse();

    virtual void KeyCallbackFunc(GLFWwindow* window, int key, int scanmode, int action, int mode);

    virtual void MouseCallbackFunc(GLFWwindow* window, int bt, int action, int mode);

    virtual void ScrollCallback(GLFWwindow* window, double x, double y);

    virtual void MousePositionCallback(GLFWwindow* window, double x, double y);

    virtual void InitApp() = 0;

    virtual void UpdateApp() = 0;

    virtual void RunApp();

    virtual void TerminateApp();
};

#endif