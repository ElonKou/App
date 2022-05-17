#pragma once

#include "Application.hh"
#include "Menu.hh"
#include "WindowBase.hh"

class ControlWindow : public WindowBase {
  private:
    float value;

  public:
    ControlWindow() { value = 10.0f; }

    ~ControlWindow() {}

    void Show() {
        if (ImGui::Begin("ControlWindow")) {
            if (ImGui::Button("OK")) {
                std::cout << "Click button" << std::endl;
            }
            ImGui::SliderFloat("value", &value, 0.0, 100.0, "%.3f");
            ImGui::End();
        }
    }
};

class DisplyWindow {
  public:
    DisplyWindow() {}

    ~DisplyWindow() {}

    void Show() {
        if (ImGui::Begin("DisplyWindow")) {
            ImGui::End();
        }
    }
};

class AppDemo : public Application {
  private:
    std::shared_ptr<Menu>          menu;
    std::shared_ptr<ControlWindow> cwin;
    std::shared_ptr<DisplyWindow>  dwin;

  public:
    AppDemo();

    ~AppDemo();

    void MousePositionCallback(GLFWwindow* window, double x, double y) override;

    virtual void InitApp() override;

    virtual void UpdateApp() override;
};
