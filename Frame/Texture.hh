#pragma once
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "Base.hh"
#include "Shader.hh"
#include <GL/glew.h>
#include <iostream>
#include <string>

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Texture {
  private:
    // static int     cnt;
    // unsigned char* image;
    int width;
    int height;
    int channel;
    // GLuint         texture;
    // int            texture_ids[16];

  public:
    unsigned int id;
    std::string  type;
    std::string  path;

    Texture();

    Texture(std::string filename, std::string path);

    ~Texture();

    void Bind();

    void UnBind();
};

#endif