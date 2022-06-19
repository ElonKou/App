#pragma once

#include "imgui_app_tools.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

class SimpleImage {
  public:
    int            width;
    int            height;
    int            channel;
    GLenum         format;
    GLuint         img_id; // Texture id
    ImVec2         size;   // image size
    unsigned char* data;   // origin data

    SimpleImage();

    SimpleImage(std::string path);

    ~SimpleImage();

    // updload into GPU memory.
    void UploadImage();

    void GenerateImage(int w, int h, int c);

    inline glm::vec3 ReadPixel(const int& w, const int& h) {
        unsigned char r = data[(h * width + w) * 3 + 0];
        unsigned char g = data[(h * width + w) * 3 + 1];
        unsigned char b = data[(h * width + w) * 3 + 2];
        return glm::vec3(r * 1.0 / 255, g * 1.0 / 255, b * 1.0 / 255);
    }

    inline void SetPixel(const int& w, const int& h, const glm::vec3& v) {
        if (w > width || w < 0 || h > height || h < 0)
            std::cout << "Error image index" << std::endl;
        if (data) {
            data[(h * width + w) * 3 + 0] = (unsigned char)(255.0f * glm::clamp(v.x, 0.0f, 0.999999f));
            data[(h * width + w) * 3 + 1] = (unsigned char)(255.0f * glm::clamp(v.y, 0.0f, 0.999999f));
            data[(h * width + w) * 3 + 2] = (unsigned char)(255.0f * glm::clamp(v.z, 0.0f, 0.999999f));
            // data[(h * width + w) * 3 + 0] = (unsigned char)255 * v.x;
            // data[(h * width + w) * 3 + 1] = (unsigned char)255 * v.y;
            // data[(h * width + w) * 3 + 2] = (unsigned char)255 * v.z;
        }
    }
};
