/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : imgui_app_tools.cpp
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Sun May 15 11:32:39 2022
================================================================*/

#include "imgui_app_tools.h"

vec2i ImVec2vec2i(ImVec2& v) {
    return vec2i(int(v.x), int(v.y));
}

ImVec2 vec2iImVec2(vec2i& v) {
    return ImVec2(v.x, v.y);
}

bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height) {
    // Load from file
    int            image_width  = 0;
    int            image_height = 0;
    unsigned char* image_data   = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width   = image_width;
    *out_height  = image_height;

    return true;
}

bool LoadImageFromFile(const char* filename, unsigned char** data_, GLuint* out_texture, int* out_width, int* out_height, int* out_channel, GLenum* format) {
    // Load from file [no free data]
    int image_width  = 0;
    int image_height = 0;
    int nrComponents = 0;
    // stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename, &image_width, &image_height, &nrComponents, 0);
    if (data == NULL)
        return false;

    *data_         = data;
    GLenum format_ = GL_RGB;
    if (nrComponents == 1) {
        format_ = GL_RED;
    } else if (nrComponents == 3) {
        format_ = GL_RGB;
    } else if (nrComponents == 4) {
        format_ = GL_RGBA;
    }

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, format_, image_width, image_height, 0, format_, GL_UNSIGNED_BYTE, data);

    *out_texture = image_texture;
    *out_width   = image_width;
    *out_height  = image_height;
    *out_channel = nrComponents;
    *format      = format_;
    return true;
}

bool SetImageData(unsigned char* data, GLuint texture_id, int width, int height, GLenum format) {
    if (data == NULL)
        return false;

    glBindTexture(GL_TEXTURE_2D, texture_id);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    return true;
}