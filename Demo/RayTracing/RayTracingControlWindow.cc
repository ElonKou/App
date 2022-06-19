/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : RayTracingControlWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Wed Jun 15 22:19:31 2022
================================================================*/

#include "RayTracingControlWindow.hh"

RayTracingControlWindow::RayTracingControlWindow() {
}

RayTracingControlWindow::~RayTracingControlWindow() {
}

void RayTracingControlWindow::Show() {
    if (ImGui::Begin("RayTracingControlWindow")) {
        if (core) {
            ImGui::TextColored(ImColor(ImVec4(0.8f, 0.3f, 0.4f, 1.0f)), "Render");
            ImGui::SliderFloat("Gamma", &core->gamma, 0.1, 10.0, "%0.3f");
            ImGui::SliderInt("Samples", &core->samples, 1, 500, "%d per pixels");
            ImGui::SliderInt("Depth", &core->max_depth, 1, 100, "%d");
            ImGui::Separator();
            ImGui::TextColored(ImColor(ImVec4(0.8f, 0.3f, 0.4f, 1.0f)), "Camera");
            ImGui::SameLine();
            if (ImGui::Button("reset")) {
                core->ResetCamera();
            }
            ImGui::InputFloat3("lookfrom", &core->cam->look_from.x);
            ImGui::InputFloat3("lookat", &core->cam->look_at.x);
            ImGui::SliderFloat("vfov", &core->cam->v_fov, 1.0f, 270.0f, "%.3f degrees");
            ImGui::SliderFloat("aperture", &core->cam->aperture, 0.0f, 100.0f, "%.3f");
            ImGui::SliderFloat("focus", &core->cam->focus_dist, 0.0f, 50.0f, "%.3f");
            ImGui::Separator();
            if (ImGui::Button("Change for Test")) {
                core->cam->Init();
                core->ChangeColor();
            }
            if (ImGui::Button("TayTracing Render")) {
                core->cam->Init();
                core->Render();
            }
        }
        ImGui::End();
    }
}