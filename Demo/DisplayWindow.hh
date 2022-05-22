#pragma once

#include "SimpleImage.hh"
#include "WindowBase.hh"

class DisplyWindow : public WindowBase {
  private:
    std::shared_ptr<SimpleImage> img;

  public:
    DisplyWindow() {
        std::string path = APP_INSTALL_PATH "/resources/images/gESgL.jpeg";
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
                for (size_t i = 0; i < 1024 * 50; i++) {
                    img->data[i * 4 + 3] = 10;
                }
                img->Upload();
            }

            ImGui::End();
        }
    }
};