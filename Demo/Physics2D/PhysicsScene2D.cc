/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : PhysicsScene2D.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Sat Jun 11 16:31:06 2022
================================================================*/

#include "PhysicsScene2D.hh"

PhysicsScene2D::PhysicsScene2D() {
    obj_cnt  = 25;
    link_cnt = 10;
    gravity  = glm::vec2(0.0f, 9.8f);
    BuildScene();
}

PhysicsScene2D::~PhysicsScene2D() {
}

void PhysicsScene2D::BuildScene() {
    // add all objects.
    for (size_t i = 0; i < obj_cnt; i++) {
        Circle c;
        c.Init();
        objects.push_back(c);
    }
    // create all links objets and all links.
    for (size_t i = 0; i < link_cnt; i++) {
        Circle c;
        c.Init();
        c.pos     = glm::vec2((0.5 / (link_cnt - 1)) * i + 0.25, 0.4);
        c.old_pos = c.pos;
        c.radius  = 0.02;
        if (i == 0 || i == (link_cnt - 1)) {
            c.fixed = true;
        }
        if (i > 0) {
            AddLink(objects.size() - 1, objects.size(), 0.065);
        }
        objects.push_back(c);
    }

    for (size_t i = 0; i < 4; i++) {
        Circle c;
        c.Init();
        c.pos     = glm::vec2(0.15, 0.05 * i + 0.45);
        c.old_pos = c.pos;
        c.radius  = 0.02;
        if (i == 0 || i == (link_cnt - 1)) {
            c.fixed = true;
        }
        if (i > 0) {
            AddLink(objects.size() - 1, objects.size(), 0.065);
        }
        objects.push_back(c);
    }

    for (size_t i = 0; i < 4; i++) {
        Circle c;
        c.Init();
        c.pos     = glm::vec2(0.85, 0.05 * i + 0.45);
        c.old_pos = c.pos;
        c.radius  = 0.02;
        if (i == 0 || i == (link_cnt - 1)) {
            c.fixed = true;
        }
        if (i > 0) {
            AddLink(objects.size() - 1, objects.size(), 0.065);
        }
        objects.push_back(c);
    }
}

void PhysicsScene2D::AddObject(glm::vec2 pos, glm::vec2 acc) {
    Circle c;
    c.Init();
    c.old_pos = c.pos = pos;
    c.accerleration   = glm::vec2(glm::cos(glfwGetTime() * 0.3) * 500,
                                glm::sin(glfwGetTime() * 0.3) * 500);
    c.col             = glm::vec4(glm::sin(glfwGetTime() * 0.31) * 0.5 + 0.5,
                      glm::sin(glfwGetTime() * 0.27) * 0.5 + 0.5,
                      glm::cos(glfwGetTime() * 0.22) * 0.5 + 0.5,
                      1.0f);
    objects.push_back(c);
}

void PhysicsScene2D::AddLink(size_t na, size_t nb, float dist) {
    PhysicsLink2D link;
    link.node_a = na;
    link.node_b = nb;
    link.dist   = dist;
    links.push_back(link);
}
