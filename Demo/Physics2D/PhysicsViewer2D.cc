/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : PhysicsViewer2D.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Thu Jun  9 12:40:18 2022
================================================================*/

#include "PhysicsViewer2D.hh"

using namespace cpptools;

PhysicsViewer2D::PhysicsViewer2D() {}

PhysicsViewer2D::~PhysicsViewer2D() {}

void PhysicsViewer2D::Show() {
    if (ImGui::Begin("PhysicsViewer2D")) {
        if (phy) {
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            ImRect      content   = ImGui::GetCurrentWindow()->InnerRect;
            ImVec2      wsize     = content.Max - content.Min;
            ImVec2      center    = wsize * 0.5 + content.Min;
            float       size      = glm::min(content.Max.y - content.Min.y, content.Max.x - content.Min.x);
            draw_list->AddCircleFilled((content.Min + content.Max) * 0.5, size * 0.5, ImColor(ImVec4(0.08, 0.08, 0.08, 1.0)), 80);

            // draw link line.
            for (size_t i = 0; i < scene->links.size(); i++) {
                Circle& a     = scene->objects[scene->links[i].node_a];
                Circle& b     = scene->objects[scene->links[i].node_b];
                ImVec4  col   = ImVec4(a.col.x, a.col.y, a.col.z, a.col.w);
                ImVec2  pos_a = (wsize - ImVec2(size, size)) * 0.5 + ImVec2(a.pos.x, a.pos.y) * size + content.Min;
                ImVec2  pos_b = (wsize - ImVec2(size, size)) * 0.5 + ImVec2(b.pos.x, b.pos.y) * size + content.Min;
                draw_list->AddLine(pos_a, pos_b, ImColor(col), 4.0f);
            }
            // draw objects.
            for (size_t i = 0; i < scene->objects.size(); i++) {
                Circle& c   = scene->objects[i];
                ImVec4  col = ImVec4(c.col.x, c.col.y, c.col.z, c.col.w);
                ImVec2  pos = (wsize - ImVec2(size, size)) * 0.5 + ImVec2(c.pos.x, c.pos.y) * size + content.Min;
                draw_list->AddCircleFilled(pos, c.radius * size, ImColor(col), 30);
            }

            // check mouse event
            ImGuiIO& io = ImGui::GetIO();
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
                ImVec2 dist_vec = io.MousePos - center;
                float  dist     = std::sqrt(dist_vec.x * dist_vec.x + dist_vec.y * dist_vec.y);
                if (dist < size * 0.5) {
                    ImVec2 p = (io.MousePos - content.Min - (wsize - ImVec2(size, size)) * 0.5) / size;
                    scene->AddObject(glm::vec2(p.x, p.y));
                }
            }
        }
        ImGui::End();
    }
}
