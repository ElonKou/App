/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : core/Menu.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Sun May 15 11:32:39 2022
================================================================*/

#include "Menu.hh"

Menu::Menu() {}

Menu::~Menu() {
    std::cout << "destructor Menu" << std::endl;
}

void Menu::ShowMenuFile() {
    if (ImGui::MenuItem("Save", "Ctrl+S")) {
    }
    if (ImGui::MenuItem("Save As..")) {
    }
    ImGui::Separator();
    if (ImGui::BeginMenu("Preferences")) {
        static bool enabled = true;
        ImGui::MenuItem("auto save", "", &enabled);
        ImGui::MenuItem("Author");
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Colors")) {
        float sz = ImGui::GetTextLineHeight();
        for (int i = 0; i < ImGuiCol_COUNT; i++) {
            const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
            ImVec2      p    = ImGui::GetCursorScreenPos();
            ImGui::GetWindowDrawList()->AddRectFilled(
                p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
            ImGui::Dummy(ImVec2(sz, sz));
            ImGui::SameLine();
            ImGui::MenuItem(name);
        }
        ImGui::EndMenu();
    }
}

void Menu::Show() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ShowMenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {
            }
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Copy", "CTRL+C")) {
            }
            if (ImGui::MenuItem("Cut", "CTRL+X")) {
            }
            if (ImGui::MenuItem("Paste", "CTRL+V")) {
            }
            ImGui::EndMenu();
        }
    }

    // if (ImGui::BeginMenu("Theme")) {
    //     if (ImGui::MenuItem("Dark theme")) {
    //         viewport->SetDarkTheme();
    //     }
    //     if (ImGui::MenuItem("Light theme")) {
    //         viewport->SetWhiteTheme();
    //     }
    //     if (ImGui::MenuItem("Github theme")) {
    //     }
    //     ImGui::EndMenu();
    // }
    if (ImGui::BeginMenu("help")) {
        if (ImGui::MenuItem("Simple")) {
        }
        ImGui::SameLine();
        showHelpMarker("This is a simple text for help.");
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
}
