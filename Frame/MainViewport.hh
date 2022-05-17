#pragma once
#ifndef MAIN_WINDOW_HH_
#define MAIN_WINDOW_HH_

#include "WindowBase.hh"

class Application;

class WindowInfo {
  public:
    int         width;
    int         height;
    float       font_size;
    std::string title;
    std::string author;
    std::string version;
    std::string fonts_path;
    ImVec4      bgcolor;
    WindowInfo() {
        width      = 1280;
        height     = 720;
        font_size  = 18.0f;
        title      = "SomeAppDemo";
        author     = "elonkou";
        version    = "v0.0.1";
        fonts_path = APP_INSTALL_PATH "/resources/fonts/YaHei.Consolas.1.12.ttf";
        bgcolor    = ImVec4(0.12, 0.12, 0.12, 1.0);
    }
    ~WindowInfo() {}
};

class MainViewport {
  public:
    GLFWwindow* window;
    WindowInfo  winfo;     // windows information.
    bool        isrunning; // target for mainviewport running flag.

    MainViewport();

    MainViewport(WindowInfo& winfo);

    ~MainViewport();

    void StartWindow(Application& app);

    void SetDarkTheme();

    void SetWhiteTheme();

    void TerminateWindow();

  private:
    GLFWwindow* InitWindow();

    void SetCallback(Application& app);

    void SetGL();

    void SetIcon();

    void LoadFont();

    void ShowDcokSpace();

    void ShowDisabledMessage();
};

#endif
