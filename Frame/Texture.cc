/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : Texture.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Fri 24 Apr 2020 12:25:48 AM CST
================================================================*/

#define STB_IMAGE_IMPLEMENTATION
#include "Texture.hh"

int Texture::cnt = 0;

Texture::Texture() {
    image = nullptr;
}

Texture::Texture(std::string filename) {
    texture_ids[0]  = GL_TEXTURE0;
    texture_ids[1]  = GL_TEXTURE1;
    texture_ids[2]  = GL_TEXTURE2;
    texture_ids[3]  = GL_TEXTURE3;
    texture_ids[4]  = GL_TEXTURE4;
    texture_ids[5]  = GL_TEXTURE5;
    texture_ids[6]  = GL_TEXTURE6;
    texture_ids[7]  = GL_TEXTURE7;
    texture_ids[8]  = GL_TEXTURE8;
    texture_ids[9]  = GL_TEXTURE9;
    texture_ids[10] = GL_TEXTURE10;
    texture_ids[11] = GL_TEXTURE11;
    texture_ids[12] = GL_TEXTURE12;
    texture_ids[13] = GL_TEXTURE13;
    texture_ids[14] = GL_TEXTURE14;
    texture_ids[15] = GL_TEXTURE15;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // #if defined(__UNIX__)
    // old version in OpenGL : 4.5
    // glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // #endif
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    channel = 4;
    stbi_set_flip_vertically_on_load(true);
    // image = stbi_load(filename.c_str(), &width, &height, NULL, 4);
    image = stbi_load(filename.c_str(), &width, &height, &channel, 0);
    if (!image) {
        std::cout << "ERROR load image: " << filename << std::endl;
    }
    std::cout << "sss" << channel << std::endl;

    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    cur_id = cnt;
    cnt++;
}

Texture::~Texture() {
}

void Texture::Bind() {
    glActiveTexture(texture_ids[cur_id]);
    glBindTexture(GL_TEXTURE_2D, texture);
}
void Texture::UnBind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}