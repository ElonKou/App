/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : Coord.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Sat Feb 19 19:46:23 2022
================================================================*/

#include "Coord.hh"

using namespace std;

Coord::Coord() {
    grid_cnt     = 20;
    grid_range   = 2.0f;
    grid_size    = 0.002f;
    grid_shader  = new Shader({APP_SHADERS_PATH "/coord_grid.vs", APP_SHADERS_PATH "/coord_grid.fs"});
    color_shader = new Shader({APP_SHADERS_PATH "/dynamic_color.vs", APP_SHADERS_PATH "/dynamic_color.fs"});

    grid_plane_x = GetPlaneMesh(0);
    grid_plane_y = GetPlaneMesh(1);
    grid_plane_z = GetPlaneMesh(2);
    grid_box     = GetBoxMesh();
    grid_pyramid = GetPyramidMesh();
}

Coord::~Coord() {
    if (color_shader) {
        delete color_shader;
    }
    if (grid_shader) {
        delete grid_shader;
    }
}

void Coord::Draw() {
    float     col = 0.8;
    glm::mat4 model;
    glm::vec3 mycolor;

    // for display axis.
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // plane z
    mycolor            = glm::vec3(0.0, 0.0, col);
    grid_plane_z.scale = glm::vec3(grid_range, grid_range, grid_range);
    model              = grid_plane_z.GetModelMatrix();
    grid_shader->Use();
    grid_shader->SetMat4f("model", model);
    grid_shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_plane_z.Draw(*grid_shader);

    grid_box.scale = glm::vec3(0.008, 0.008, grid_range);
    model          = grid_box.GetModelMatrix();
    color_shader->Use();
    color_shader->SetMat4f("model", model);
    color_shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_box.Draw(*color_shader);

    grid_pyramid.rotation = glm::vec3(0.0, 0.0, 0.0);
    grid_pyramid.pos      = glm::vec3(0.0, 0.0, grid_range / 2.0);
    grid_pyramid.scale    = glm::vec3(0.03, 0.03, 0.06);
    model                 = grid_pyramid.GetModelMatrix();
    color_shader->Use();
    color_shader->SetMat4f("model", model);
    color_shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_pyramid.Draw(*color_shader);

    // plane x
    mycolor            = glm::vec3(col, 0.0, 0.0);
    grid_plane_x.scale = glm::vec3(grid_range, grid_range, grid_range);
    model              = grid_plane_x.GetModelMatrix();
    grid_shader->Use();
    grid_shader->SetMat4f("model", model);
    grid_shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_plane_x.Draw(*grid_shader);

    grid_box.scale = glm::vec3(grid_range, 0.008, 0.008);
    model          = grid_box.GetModelMatrix();
    color_shader->Use();
    color_shader->SetMat4f("model", model);
    color_shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_box.Draw(*color_shader);

    grid_pyramid.rotation = glm::vec3(0.0, glm::radians(90.0), 0.0);
    grid_pyramid.pos      = glm::vec3(grid_range / 2.0, 0.0, 0.0);
    grid_pyramid.scale    = glm::vec3(0.03, 0.03, 0.06);
    model                 = grid_pyramid.GetModelMatrix();
    color_shader->Use();
    color_shader->SetMat4f("model", model);
    color_shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_pyramid.Draw(*color_shader);

    // plane y
    mycolor            = glm::vec3(0.0, col, 0.0);
    grid_plane_y.scale = glm::vec3(grid_range, grid_range, grid_range);
    model              = grid_plane_y.GetModelMatrix();
    grid_shader->Use();
    grid_shader->SetMat4f("model", model);
    grid_shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_plane_y.Draw(*grid_shader);

    grid_box.scale = glm::vec3(0.008, grid_range, 0.008);
    model          = grid_box.GetModelMatrix();
    color_shader->Use();
    color_shader->SetMat4f("model", model);
    color_shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_box.Draw(*color_shader);

    grid_pyramid.rotation = glm::vec3(glm::radians(-90.0), 0.0, 0.0);
    grid_pyramid.pos      = glm::vec3(0.0, grid_range / 2.0, 0.0);
    grid_pyramid.scale    = glm::vec3(0.03, 0.03, 0.06);
    model                 = grid_pyramid.GetModelMatrix();
    color_shader->Use();
    color_shader->SetMat4f("model", model);
    color_shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_pyramid.Draw(*color_shader);

    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
}

void Coord::CameraUpdate(glm::mat4& render_mat) {
    grid_shader->Use();
    grid_shader->SetMat4f("renderMat", render_mat);
    color_shader->Use();
    color_shader->SetMat4f("renderMat", render_mat);
}