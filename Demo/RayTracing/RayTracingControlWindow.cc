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
        if (img) {
            if (ImGui::Button("change")) {
                for (size_t i = 0; i < img->height; i++) {
                    for (size_t j = 0; j < img->width; j++) {
                        img->SetPixel(j, i, glm::vec3(i * 1.0 / img->height, j * 1.0 / img->width, 0.5));
                    }
                }
                img->Upload();
            }
        }
        ImGui::End();
    }
}