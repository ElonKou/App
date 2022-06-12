/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : Texture.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Fri 24 Apr 2020 12:25:48 AM CST
================================================================*/

#define STB_IMAGE_IMPLEMENTATION
#include "Texture.hh"

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma) {
    std::string filename = std::string(path);
    filename             = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width        = 0;
    int height       = 0;
    int nrComponents = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format = GL_RGB;
        if (nrComponents == 1) {
            format = GL_RED;
        } else if (nrComponents == 3) {
            format = GL_RGB;
        } else if (nrComponents == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    return textureID;
}

Texture::Texture() {
}

Texture::Texture(std::string filename, std::string path_) {
    id   = TextureFromFile(filename.c_str(), path_);
    type = "texture_diffuse";
    path = path_;
}

Texture::~Texture() {
}

void Texture::Bind() {
    // glActiveTexture(texture_ids[cur_id]);
    glActiveTexture(GL_TEXTURE0 + id);
    glBindTexture(GL_TEXTURE_2D, id);
}
void Texture::UnBind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
