#pragma once
#ifndef WINDOW_BASE_HH_
#define WINDOW_BASE_HH_

#include "Base.hh"

class WindowBase : public Base {
  public:
    WindowBase() {}

    virtual ~WindowBase() {}

    // draw element.
    virtual void Show() = 0;

    void showHelpMarker(const std::string dsec) {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(dsec.c_str());
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }
};

#endif