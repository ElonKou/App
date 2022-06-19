#pragma once

#include "Base.hh"
#include "Ray.hh"

class RayTracingCamera {
  private:
    float     viewport_width;  // render range depended height.
    float     viewport_height; // render range [-1.0, 1.0].

    glm::vec3 u; // horizontal vector.
    glm::vec3 v; // vertical  vector.
    glm::vec3 w; // look vector.

  public:
    glm::vec3 look_from;       // look from position.
    glm::vec3 look_at;         // look at position.
    glm::vec3 v_up;            // vertical vecor.
    int       image_width;  // image width and height.
    int       image_height; // image width and height.
    glm::vec3 ori;          // origin position of camera.
    glm::vec3 horizontal;   // horizontal vector.
    glm::vec3 vertical;     // vertical vector.
    glm::vec3 center;       // camera viewport center position.
    float     v_fov;        // vertical fov.
    float     aperture;     // aperture of camera.
    float     focus_dist;   // focus distance.

    RayTracingCamera() {
        look_from    = glm::vec3(0.0f, 0.0f, 0.0f);
        look_at      = glm::vec3(0.0f, 0.0f, -1.0f);
        v_up         = glm::vec3(0.0f, 1.0f, 0.0f);
        image_width  = 960;
        image_height = 540;
        v_fov        = 90.0f;
        aperture     = 0.1f;
        focus_dist   = glm::length(look_from - look_at);
        Init();
    }

    RayTracingCamera(const glm::vec3& lookfrom, const glm::vec3& lookat, const glm::vec3 vup, float vfov, float aperture_, float focusdist)
        : look_from(lookfrom)
        , look_at(lookat)
        , v_up(vup)
        , v_fov(vfov)
        , aperture(aperture_)
        , focus_dist(focusdist) {
        image_width  = 960;
        image_height = 540;
        Init(); // Init Camera.
    }

    void Init() {
        viewport_height = 2.0f * tan(glm::radians(v_fov) / 2.0f);         // we will render vertical position from -1.0 to 1.0;
        viewport_width  = (viewport_height / image_height) * image_width; // deepending height.

        w = glm::normalize(look_from - look_at);
        u = glm::normalize(glm::cross(v_up, w));
        v = glm::cross(w, u);

        ori        = look_from;
        horizontal = viewport_width * u * focus_dist;
        vertical   = viewport_height * v * focus_dist;
        center     = ori - horizontal * 0.5f - vertical * 0.5f - w * focus_dist;
    }

    ~RayTracingCamera() {}

    inline Ray GetRay(float u_value, float v_value) {
        glm::vec3 rd     = aperture * 0.5f * GetRandomPlaneVector();
        glm::vec3 offset = u * rd.x + v * rd.y;
        return Ray(ori + offset, glm::vec3(center + horizontal * u_value + vertical * v_value - ori - offset));
        // return Ray(ori, glm::vec3(center + horizontal * u_value + vertical * v_value - ori));
    }
};
