/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : OpenGLWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Sat May 21 17:22:56 2022
================================================================*/

#include "OpenGLWindow.hh"

OpenGLWindow::OpenGLWindow() {
    scene   = nullptr;
    ret     = false;
    fbuffer = std::make_shared<FrameBuffer>();
}

OpenGLWindow::~OpenGLWindow() {
}

void OpenGLWindow::Show() {
    if (ImGui::Begin("OpenGLWindow")) {
        if (scene && fbuffer && cam) {
            ImVec2 window_size = ImGui::GetCurrentWindow()->Size * 2 - ImVec2(0, 64);
            cam->cam_width     = window_size.x;
            cam->cam_height    = window_size.y;
            if (!ret) {
                fbuffer->CreateBuffer(window_size.x, window_size.y);
                ret = true;
            }
            fbuffer->Bind();
            scene->Draw(*cam.get());
            fbuffer->Unbind();

            uint64_t textureID = fbuffer->GetTextureId();
            ImGui::Image(reinterpret_cast<void*>(textureID), window_size / 2, ImVec2{0, 1}, ImVec2{1, 0});
        }
        ImGui::End();
    }
}