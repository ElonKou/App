/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : PhysicsLink2D.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Fri Jun 10 19:07:34 2022
================================================================*/

#include "PhysicsLink2D.hh"

PhysicsLink2D::PhysicsLink2D() {
    node_a = -1;
    node_b = -1;
    dist   = 0.05;
}

PhysicsLink2D::~PhysicsLink2D() {
}

void PhysicsLink2D::ApplyPhysicsLink2D(Circle& na, Circle& nb) {
    if (node_a >= 0 && node_b >= 0) {
        glm::vec2 dist_vec = nb.pos - na.pos;
        float     len      = glm::length(dist_vec);
        if (len > dist) {
            glm::vec2 n  = glm::normalize(dist_vec);
            float     ra = (na.radius) / (na.radius + nb.radius);
            float     rb = (nb.radius) / (na.radius + nb.radius);
            if (na.fixed) {
                ra = 1.0;
                rb = 0.0;
            }
            if (nb.fixed) {
                ra = 0.0;
                rb = 1.0;
            }
            na.pos = na.pos - n * (dist - len) * rb;
            nb.pos = nb.pos + n * (dist - len) * ra;
        }
    }
}
