/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : SimpleImage.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Tue May 17 22:21:25 2022
================================================================*/

#include "SimpleImage.hh"

SimpleImage::SimpleImage()
    : width(0)
    , height(0)
    , channel(0)
    , format(GL_RGB)
    , data(NULL) {
}

SimpleImage::SimpleImage(std::string path)
    : width(0)
    , height(0)
    , channel(0)
    , format(GL_RGB)
    , data(NULL) {

    bool ret = LoadImageFromFile(path.c_str(), &data, &img_id, &width, &height, &channel, &format);
    size     = ImVec2(width, height);
    if (!ret) {
        std::cout << "Load image failed!" << std::endl;
    }
}

SimpleImage::~SimpleImage() {
    if (!data) {
        stbi_image_free(data);
    }
}

void SimpleImage::UploadImage() {
    if (data) {
        bool ret = SetImageData(data, img_id, width, height, format);
        if (!ret) {
            std::cout << "Uoload image failed!" << std::endl;
        }
    }
}

void SimpleImage::GenerateImage(int w, int h, int c) {
    width   = w;
    height  = h;
    channel = c;
    format  = GL_RGB;
    data    = (unsigned char*)malloc(width * height * channel * sizeof(unsigned char));
    memset(data, 0, width * height * channel);
    if (!data) {
        std::cout << "Create image failed!" << std::endl;
        exit(0);
    }

    glGenTextures(1, &img_id);
    glBindTexture(GL_TEXTURE_2D, img_id);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (void*)data);

    size = ImVec2(width, height);
}
