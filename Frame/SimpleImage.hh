#pragma once

#include "imgui_app_tools.h"

class SimpleImage {
  public:
    int            width;
    int            height;
    int            channel;
    GLuint         img_id; // Texture id
    ImVec2         size;   // image size
    unsigned char* data;   // origin data

    SimpleImage();

    SimpleImage(std::string path);

    ~SimpleImage();

    // updload into GPU memory.
    void Upload();
};
