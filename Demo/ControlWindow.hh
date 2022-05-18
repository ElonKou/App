#pragma once

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