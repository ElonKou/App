#pragma once

#include "Application.hh"
#include "Camera.hh"
#include "ControlWindow.hh"
#include "DisplayWindow.hh"
#include "Menu.hh"
#include "OpenGLWindow.hh"
#include "Scene.hh"

class ViewDemo : public Application {
  private:
    std::shared_ptr<Menu>          menu;
    std::shared_ptr<ControlWindow> cwin;
    std::shared_ptr<DisplyWindow>  dwin;
    std::shared_ptr<OpenGLWindow>  owin;

    std::shared_ptr<Scene> scene;
    std::shared_ptr<Mesh>  box;
    std::shared_ptr<Model> model;

  public:
    ViewDemo() {}

    ~ViewDemo() {}

    void KeyCallbackFunc(GLFWwindow* window, int key, int scanmode, int action, int mode) override;

    void MouseCallbackFunc(GLFWwindow* window, int bt, int action, int mode) override;

    void ScrollCallback(GLFWwindow* window, double x, double y) override;

    void MousePositionCallback(GLFWwindow* window, double x, double y) override;

    virtual void InitApp() override;

    virtual void UpdateApp() override;
};
