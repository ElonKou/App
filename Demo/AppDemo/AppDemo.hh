#pragma once

#include "Application.hh"
#include "ControlWindow.hh"
#include "DisplayWindow.hh"
#include "Menu.hh"

class AppDemo : public Application {
  private:
    std::shared_ptr<Menu>          menu;
    std::shared_ptr<ControlWindow> cwin;
    std::shared_ptr<DisplyWindow>  dwin;

  public:
    void MousePositionCallback(GLFWwindow* window, double x, double y) override;

    virtual void InitApp() override;

    virtual void UpdateApp() override;
};
