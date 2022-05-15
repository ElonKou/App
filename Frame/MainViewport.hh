#pragma once
#ifndef MAIN_WINDOW_HH_
#define MAIN_WINDOW_HH_

#include "Menu.hh"
#include "WindowBase.hh"

using namespace std;

class MainViewport : public WindowBase {
  public:
    GLFWwindow* window;

    Menu* menu;

    struct WindowInfo {
        int width;

        int height;

        float font_size;

        string title;

        string fonts_path;

        ImVec4 bgcolor;
    } win_info;

    MainViewport();

    ~MainViewport();

    GLFWwindow* InitWindow();

    virtual void Show();

    void StartWindow();

    void SetGL(GLFWwindow* window);

    void SetIcon(GLFWwindow* window);

    void LoadFont();

    void ShowDcokSpace();

    void ShowDisabledMessage();

    void SetDarkTheme();

    void SetWhiteTheme();

    static void OnKeyBack(GLFWwindow* window, int key, int scanmode, int key_action, int mode);
};

#endif
