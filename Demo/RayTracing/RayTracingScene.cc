/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : RayTracingScene.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Thu Jun 16 22:29:53 2022
================================================================*/

#include "RayTracingScene.hh"

bool RayTracingScene::Hit(Ray& r, float t_min, float t_max, RayHitRecord& rec) {
    bool         hit_any  = false;
    float        cloest_t = t_max; // for every pixel we only need to find the most nearest point.
    RayHitRecord temp_rec;
    for (size_t i = 0; i < objects.size(); i++) {
        if (objects[i]->Hit(r, t_min, cloest_t, temp_rec)) {
            hit_any  = true;
            cloest_t = temp_rec.t; // from far to cloest.
            rec      = temp_rec;
        }
    }
    return hit_any;
}