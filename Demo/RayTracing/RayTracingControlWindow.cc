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
            if (ImGui::Button("Change for Test")) {
                core->ChangeColor();
            }
            if (ImGui::Button("TayTracing Render")) {
                core->Render();
            }
        }
        ImGui::End();
    }
}