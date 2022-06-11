/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : Physics2D.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Thu Jun  9 12:22:47 2022
================================================================*/

#include "Physics2D.hh"
#include <chrono>

Physics2D::Physics2D() {
    rows_cols = 10;
}

Physics2D::~Physics2D() {
}

void Physics2D::UpdateObjects(float dt) {
    if (!scene) {
        return;
    }
    int sub_steps = 32;
    for (size_t i = 0; i < sub_steps; i++) {
        // auto st = std::chrono::high_resolution_clock::now();
        SetVelocity();
        // auto  ed   = std::chrono::high_resolution_clock::now();
        // float dura = std::chrono::duration_cast<std::chrono::microseconds>(ed - st).count();
        // std::cout << "=================================" << std::endl;
        // std::cout << "Set       :" << dura << " ms" << std::endl;
        UpdatePosition(dt / sub_steps);
        // st   = ed;
        // ed   = std::chrono::high_resolution_clock::now();
        // dura = std::chrono::duration_cast<std::chrono::microseconds>(ed - st).count();
        // std::cout << "Update    : " << dura << " ms" << std::endl;
        ApplyBoundConstraint();
        // st   = ed;
        // ed   = std::chrono::high_resolution_clock::now();
        // dura = std::chrono::duration_cast<std::chrono::microseconds>(ed - st).count();
        // std::cout << "bound     : " << dura << " ms" << std::endl;
        ApplyLinkConstraint();
        // st   = ed;
        // ed   = std::chrono::high_resolution_clock::now();
        // dura = std::chrono::duration_cast<std::chrono::microseconds>(ed - st).count();
        // std::cout << "Link      : " << dura << " ms" << std::endl;
        SolveCollision();
        // st   = ed;
        // ed   = std::chrono::high_resolution_clock::now();
        // dura = std::chrono::duration_cast<std::chrono::microseconds>(ed - st).count();
        // std::cout << "collision : " << dura << " ms" << std::endl;
        // UpdateHashTables();
        // SolveHashCollision();
        // st   = ed;
        // ed   = std::chrono::high_resolution_clock::now();
        // dura = std::chrono::duration_cast<std::chrono::microseconds>(ed - st).count();
        // std::cout << "HASH_fast : " << dura << " ms" << std::endl;
    }
}

void Physics2D::UpdateHashTables() {
    // rebuild hash tables.
    if (hashtables.size() < 1) {
        for (size_t i = 0; i < rows_cols * rows_cols; i++) { // rows.
            hashtables[i] = std::set<int>();
        }
    } else {
        for (size_t i = 0; i < hashtables.size(); i++) {
            std::cout << hashtables[i].size() << " ";
            hashtables[i].clear();
        }
    }

    // compute the new ID.
    for (size_t i = 0; i < scene->objects.size(); i++) {
        glm::vec2& pos = scene->objects[i].pos;
        size_t     id  = int(pos.y * rows_cols) * rows_cols + int(pos.x * rows_cols);
        hashtables[id].emplace(i); // store objects ID.
    }
}

void Physics2D::SetVelocity() {
    for (size_t i = 0; i < scene->objects.size(); i++) {
        scene->objects[i].accerleration += scene->gravity;
    }
}

void Physics2D::UpdatePosition(float dt) {
    for (size_t i = 0; i < scene->objects.size(); i++) {
        Circle&   c   = scene->objects[i];
        glm::vec2 vel = c.pos - c.old_pos;
        c.old_pos     = c.pos;
        if (!c.fixed) {
            c.pos = c.pos + vel + c.accerleration * dt * dt;
        }
        c.accerleration = glm::vec2(0.0f);
    }
}

void Physics2D::ApplyBoundConstraint() {
    glm::vec2 center = glm::vec2(0.5f);
    float     r      = 0.5;
    for (size_t i = 0; i < scene->objects.size(); i++) {
        Circle&   c        = scene->objects[i];
        glm::vec2 dist_vec = c.pos - center;
        float     dist     = glm::length(dist_vec);
        if (dist > r - c.radius) {
            glm::vec2 n = glm::normalize(dist_vec);
            if (!c.fixed) {
                c.pos = c.pos - n * (dist - r + c.radius);
            }
        }
    }
}

void Physics2D::ApplyLinkConstraint() {
    for (size_t i = 0; i < scene->links.size(); i++) {
        Circle& a = scene->objects[scene->links[i].node_a];
        Circle& b = scene->objects[scene->links[i].node_b];
        scene->links[i].ApplyPhysicsLink2D(a, b);
    }
}

void Physics2D::SolveHashCollision() {
    // Collision detection.
    auto UpdatePair = [](Circle& a, Circle& b) {
        glm::vec2 dist_vec = b.pos - a.pos;
        float     dist     = glm::length(dist_vec);
        if (dist < a.radius + b.radius) {
            // colve collision between two circles.
            glm::vec2 n  = glm::normalize(dist_vec);
            float     ra = (b.radius) / (a.radius + b.radius);
            float     rb = (a.radius) / (a.radius + b.radius);
            if (a.fixed && b.fixed) {
                return;
            } else if (a.fixed) {
                ra = 0.0f;
                rb = 1.0f;
            } else if (b.fixed) {
                ra = 1.0f;
                rb = 0.0f;
            }
            a.pos = a.pos + n * (dist - a.radius - b.radius) * ra;
            b.pos = b.pos - n * (dist - a.radius - b.radius) * rb;
        }
    };

    for (size_t i = 0; i < hashtables.size(); i++) {
        std::set<int>& a = hashtables[i];
        if (a.size() == 0) {
            // avoid empty block.
            continue;
        }
        std::vector<int> cc;
        for (auto x = a.begin(); x != a.end(); ++x) {
            cc.push_back(*x);
        }
        if (cc.size() > 1) {
            for (size_t u = 0; u < cc.size(); u++) {
                for (size_t v = u + 1; v < cc.size(); v++) {
                    Circle& a = scene->objects[u];
                    Circle& b = scene->objects[u];
                    UpdatePair(a, b);
                }
            }
        }

        if (i % rows_cols != (rows_cols - 1)) {
            // check with right-side block.
            for (auto x = a.begin(); x != a.end(); ++x) {
                std::set<int>& b = hashtables[i + 1];
                for (auto y = b.begin(); y != b.end(); ++y) {
                    Circle& oa = scene->objects[*x];
                    Circle& ob = scene->objects[*y];
                    UpdatePair(oa, ob);
                }
            }
        }
        if (i < rows_cols * (rows_cols - 1)) {
            // check with down-side block.
            for (auto x = a.begin(); x != a.end(); ++x) {
                std::set<int>& b = hashtables[i + rows_cols];
                for (auto y = b.begin(); y != b.end(); ++y) {
                    Circle& oa = scene->objects[*x];
                    Circle& ob = scene->objects[*y];
                    UpdatePair(oa, ob);
                }
            }
        }
    }
}

void Physics2D::SolveCollision() {
    for (size_t i = 0; i < scene->objects.size(); i++) {
        Circle& a = scene->objects[i];
        for (size_t j = i + 1; j < scene->objects.size(); j++) {
            Circle&   b        = scene->objects[j];
            glm::vec2 dist_vec = b.pos - a.pos;
            float     dist     = glm::length(dist_vec);
            if (dist < a.radius + b.radius) {
                // colve collision between two circles.
                glm::vec2 n  = glm::normalize(dist_vec);
                float     ra = (b.radius) / (a.radius + b.radius);
                float     rb = (a.radius) / (a.radius + b.radius);
                if (a.fixed && b.fixed) {
                    continue;
                } else if (a.fixed) {
                    ra = 0.0f;
                    rb = 1.0f;
                } else if (b.fixed) {
                    ra = 1.0f;
                    rb = 0.0f;
                }
                a.pos = a.pos + n * (dist - a.radius - b.radius) * ra;
                b.pos = b.pos - n * (dist - a.radius - b.radius) * rb;
            }
        }
    }
}