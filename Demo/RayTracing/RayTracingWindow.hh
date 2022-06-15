#pragma once

#include "SimpleImage.hh"
#include "WindowBase.hh"

class RayTracingWindow : public WindowBase {
  public:
    std::shared_ptr<SimpleImage> img;

    RayTracingWindow() {}

    ~RayTracingWindow() {}

    void Show() {
        if (ImGui::Begin("RayTracingWindow")) {
            if (img) {
                ImVec2      uv_min    = ImVec2(0.0f, 0.0f);             // Top-left
                ImVec2      uv_max    = ImVec2(1.0f, 1.0f);             // Lower-right
                ImVec4      tint_col  = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
                ImRect      bb        = ImGui::GetCurrentWindow()->InnerRect;
                ImVec2      wsize     = bb.Max - bb.Min;
                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                // draw_list->AddImage((void*)(intptr_t)img->img_id, bb.Min , bb.Min + wsize, uv_min, uv_max, ImColor(tint_col));
                ImVec2 offset = (wsize - img->size) * 0.5;
                draw_list->AddImage((void*)(intptr_t)img->img_id, bb.Min + offset, bb.Min + offset + img->size, uv_min, uv_max, ImColor(tint_col));
            }
            ImGui::End();
        }
    }
};