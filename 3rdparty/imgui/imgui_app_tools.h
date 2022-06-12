#pragma once
#ifndef IMGUI_APP_TOOLS_H_
#define IMGUI_APP_TOOLS_H_

#include "cpptypes.hpp"
#include "imgui.h"
#include "stb_image.h"
#include <GL/glew.h>
#include <iostream>

using namespace cpptypes;

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

vec2i ImVec2vec2i(ImVec2& v);

ImVec2 vec2iImVec2(vec2i& v);

bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);

bool LoadImageFromFile(const char* filename, unsigned char** data, GLuint* out_texture, int* out_width, int* out_height);

bool SetImageData(unsigned char* data, GLuint texture_id, int width, int height);
#endif