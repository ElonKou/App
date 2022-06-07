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
        // bool x = ImGui::IsWindowFocused();
        // std::cout << x << std::endl;
        if (scene && fbuffer) {
            ImVec2 window_st       = ImGui::GetCurrentWindow()->Pos;
            ImVec2 window_end      = ImGui::GetCurrentWindow()->Pos + ImGui::GetCurrentWindow()->Size;
            ImVec2 window_size     = ImGui::GetCurrentWindow()->Size * 2 - ImVec2(0, 64);
            scene->cam->cam_width  = window_size.x;
            scene->cam->cam_height = window_size.y;
            scene->cam->st         = glm::vec2(window_st.x, window_st.y);
            scene->cam->end        = glm::vec2(window_end.x, window_end.y);
            if (!ret) {
                fbuffer->CreateBuffer(window_size.x, window_size.y);
                ret = true;
            }
            fbuffer->Bind();
            scene->Draw();
            fbuffer->Unbind();

            uint64_t textureID = fbuffer->GetTextureId();
            ImGui::Image(reinterpret_cast<void*>(textureID), window_size / 2, ImVec2{0, 1}, ImVec2{1, 0});
        }
        ImGui::End();
    }
}