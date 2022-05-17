#pragma once

#include "Application.hh"
#include "Menu.hh"
#include "SimpleImage.hh"
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
  private:
    std::shared_ptr<SimpleImage> img;

  public:
    DisplyWindow() {
        std::string path = APP_INSTALL_PATH "/resources/images/OIP-C.jpeg";
        img              = std::make_shared<SimpleImage>(path);
    }

    ~DisplyWindow() {}

    void Show() {
        if (ImGui::Begin("DisplyWindow")) {
            ImVec2 uv_min     = ImVec2(0.0f, 0.0f);             // Top-left
            ImVec2 uv_max     = ImVec2(1.0f, 1.0f);             // Lower-right
            ImVec4 tint_col   = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
            ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
            ImGui::Image((void*)(intptr_t)img->img_id, img->size, uv_min, uv_max, tint_col, border_col);

            if (ImGui::Button("change")) {
                for (size_t i = 0; i < 1024*100; i++) {
                    img->data[i*4+3] = 10;
                }
                img->Upload();
            }

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
    void MousePositionCallback(GLFWwindow* window, double x, double y) override;

    virtual void InitApp() override;

    virtual void UpdateApp() override;
};
