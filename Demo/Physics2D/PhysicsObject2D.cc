/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : PhysicsObject2D.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Fri Jun 10 17:34:50 2022
================================================================*/

#include "PhysicsObject2D.hh"

using namespace cpptools;

void Circle::Init() {
    auto GenPos = [](float r) {
        float     dist = RandomFloat<float>() * (0.5 - r);
        float     rad  = RandomFloat<float>() * glm::pi<float>() * 2.0;
        glm::vec2 ret;
        ret.x = dist * glm::cos(rad) + 0.5;
        ret.y = dist * glm::sin(rad) + 0.5;
        return ret;
    };
    radius        = 0.02 + RandomFloat<float>() * 0.012;
    pos           = GenPos(radius);
    old_pos       = pos;
    col           = glm::vec4(RandomFloat<float>(), RandomFloat<float>(), RandomFloat<float>(), 1.0f);
    accerleration = glm::vec2(0.0f);
}