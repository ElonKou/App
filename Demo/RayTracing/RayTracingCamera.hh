#pragma once

#include "Base.hh"

class RayTracingCamera {
  private:
    float focus_length;    // focus length for render.
    float viewport_width;  // render range [-1.0, 1.0].
    float viewport_height; // render range [-1.0, 1.0].

  public:
    int       image_width;  // image width and height.
    int       image_height; // image width and height.
    glm::vec3 ori;          // origin position of camera.
    glm::vec3 horizontal;   // horizontal vector.
    glm::vec3 vertical;     // vertical vector.
    glm::vec3 center;       // camera viewport center position.

    RayTracingCamera() {
        image_width     = 960;
        image_height    = 540;
        focus_length    = 1.0f;
        viewport_height = 2.0f; // we will render vertical position from -1.0 to 1.0;
        viewport_width  = (viewport_height / image_height) * image_width;

        ori        = glm::vec3(0.0f, 0.0f, 0.0f);
        horizontal = glm::vec3(viewport_width, 0.0f, 0.0f);
        vertical   = glm::vec3(0.0f, viewport_height, 0.0f);
        center     = ori - horizontal * 0.5f - vertical * 0.5f - glm::vec3(0.0f, 0.0f, focus_length);
    }

    ~RayTracingCamera() {}
};
