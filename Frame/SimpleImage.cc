/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : SimpleImage.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Tue May 17 22:21:25 2022
================================================================*/

#include "SimpleImage.hh"

SimpleImage::SimpleImage() {
    data = NULL;
}

SimpleImage::SimpleImage(std::string path)
    : width(0)
    , height(0)
    , channel(4)
    , data(NULL) {

    bool ret = LoadImageFromFile(path.c_str(), &data, &img_id, &width, &height);
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

void SimpleImage::Upload() {
    if (data) {
        bool ret = SetImageData(data, img_id, width, height);
        if (!ret) {
            std::cout << "Uoload image failed!" << std::endl;
        }
    }
}
