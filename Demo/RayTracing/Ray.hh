#pragma once

#include "Base.hh"
#include <climits>
#include <cstdlib>
#include <ostream>

// Random part
#define Random(x) (rand() % x)

inline int GetRandomInt(int range) {
    return Random(range);
}

inline float GetRandomFloat() {
    // return GetRandomInt(1000001) / 1000000.0f;
    return rand() / (RAND_MAX + 1.0);
}

inline glm::vec3 GetRandomVec3() {
    return glm::vec3(GetRandomFloat(), GetRandomFloat(), GetRandomFloat());
}

inline glm::vec3 GetRandomVector(bool normal = true) {
    while (true) {
        glm::vec3 p = glm::vec3(GetRandomFloat() * 2.0f - 1.0f, GetRandomFloat() * 2.0f - 1.0f, GetRandomFloat() * 2.0f - 1.0f);
        if (glm::length(p) >= 1.0f) {
            continue;
        }
        if (!normal)
            return p;
        return glm::normalize(p);
    }
}

inline glm::vec3 GetRandomPlaneVector() {
    // generate vector in a plane.
    while (true) {
        auto p = glm::vec3(GetRandomFloat() * 2.0f - 1.0f, GetRandomFloat() * 2.0f - 1.0f, 0.0f);
        if (glm::length(p) >= 1.0f)
            continue;
        return p;
    }
}

inline bool NearZero(const glm::vec3& v) {
    if (glm::length(v) < 10e-7)
        return true;
    return false;
}

inline glm::vec3 Reflect(const glm::vec3& v, const glm::vec3& n) {
    // all reflect.
    return v - 2 * glm::dot(v, n) * n;
}

inline glm::vec3 Refract(const glm::vec3& v_in, const glm::vec3& n, float eta_i_o) {
    // refract the light by the v_in direction according eta.
    // eta_i_o = eta_in / eta_out;
    float cos_theta          = glm::dot(-1.0f * v_in, n);
    cos_theta                = (cos_theta < 1.0f) ? cos_theta : 1.0f;
    glm::vec3 v_out_perp     = eta_i_o * glm::vec3(v_in + cos_theta * n);
    glm::vec3 v_out_parallel = -1.0f * sqrt(1.0f - glm::length(v_out_perp) * glm::length(v_out_perp)) * n;
    return v_out_perp + v_out_parallel;
}

inline std::ostream& operator<<(std::ostream& os, const glm::vec3& n) {
    os << n.x << " " << n.y << " " << n.z;
    return os;
}

class Ray {
  public:
    Ray() {}

    Ray(const glm::vec3& origin_, const glm::vec3& direction_)
        : ori(origin_)
        , dir(direction_) {}

    ~Ray() {}

    glm::vec3 at(float t) {
        return ori + t * dir;
    }

  public:
    glm::vec3 ori;
    glm::vec3 dir;
};
