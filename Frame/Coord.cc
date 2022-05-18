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
    grid_shader  = new Shader({APP_SHADERS_PATH "/notexture.vs", APP_SHADERS_PATH "/notexture.fs"});
    color_shader = new Shader({APP_SHADERS_PATH "/colorvertex.vs", APP_SHADERS_PATH "/colorfrag.fs"});
}

Coord::~Coord() {
    if (color_shader) {
        delete color_shader;
    }
    if (grid_shader) {
        delete grid_shader;
    }
}

void Coord::Init() {
    grid_plane_x         = GetPlane3D(0);
    grid_plane_x.shader  = grid_shader;
    grid_plane_x.texture = nullptr;

    grid_plane_y         = GetPlane3D(1);
    grid_plane_y.shader  = grid_shader;
    grid_plane_y.texture = nullptr;

    grid_plane_z         = GetPlane3D(2);
    grid_plane_z.shader  = grid_shader;
    grid_plane_z.texture = nullptr;

    grid_box         = GetBox();
    grid_box.shader  = color_shader;
    grid_box.texture = nullptr;

    grid_pyramid         = GetPyramid();
    grid_pyramid.shader  = color_shader;
    grid_pyramid.texture = nullptr;

    grid_plane_x.Init();
    grid_plane_y.Init();
    grid_plane_z.Init();
    grid_box.Init();
    grid_pyramid.Init();
}

void Coord::Draw() {
    float     col     = 0.8;
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
    grid_plane_z.shader->Use();
    grid_plane_z.shader->SetMat4f("model", model);
    grid_plane_z.shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_plane_z.Draw();

    grid_box.scale = glm::vec3(0.008, 0.008, grid_range);
    model          = grid_box.GetModelMatrix();
    grid_box.shader->Use();
    grid_box.shader->SetMat4f("model", model);
    grid_box.shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_box.Draw();

    grid_pyramid.rotation = glm::vec3(0.0, 0.0, 0.0);
    grid_pyramid.pos      = glm::vec3(0.0, 0.0, grid_range / 2.0);
    grid_pyramid.scale    = glm::vec3(0.02, 0.02, 0.04);
    model                 = grid_pyramid.GetModelMatrix();
    grid_pyramid.shader->Use();
    grid_pyramid.shader->SetMat4f("model", model);
    grid_pyramid.shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_pyramid.Draw();

    // plane x
    mycolor            = glm::vec3(col, 0.0, 0.0);
    grid_plane_x.scale = glm::vec3(grid_range, grid_range, grid_range);
    model              = grid_plane_x.GetModelMatrix();
    grid_plane_x.shader->Use();
    grid_plane_x.shader->SetMat4f("model", model);
    grid_plane_x.shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_plane_x.Draw();

    grid_box.scale = glm::vec3(grid_range, 0.008, 0.008);
    model          = grid_box.GetModelMatrix();
    grid_box.shader->Use();
    grid_box.shader->SetMat4f("model", model);
    grid_box.shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_box.Draw();

    grid_pyramid.rotation = glm::vec3(0.0, glm::radians(90.0), 0.0);
    grid_pyramid.pos      = glm::vec3(grid_range / 2.0, 0.0, 0.0);
    grid_pyramid.scale    = glm::vec3(0.02, 0.02, 0.04);
    model                 = grid_pyramid.GetModelMatrix();
    grid_pyramid.shader->Use();
    grid_pyramid.shader->SetMat4f("model", model);
    grid_pyramid.shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_pyramid.Draw();

    // plane y
    mycolor            = glm::vec3(0.0, col, 0.0);
    grid_plane_y.scale = glm::vec3(grid_range, grid_range, grid_range);
    model              = grid_plane_y.GetModelMatrix();
    grid_plane_y.shader->Use();
    grid_plane_y.shader->SetMat4f("model", model);
    grid_plane_y.shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_plane_y.Draw();

    grid_box.scale = glm::vec3(0.008, grid_range, 0.008);
    model          = grid_box.GetModelMatrix();
    grid_box.shader->Use();
    grid_box.shader->SetMat4f("model", model);
    grid_box.shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_box.Draw();

    grid_pyramid.rotation = glm::vec3(glm::radians(90.0), 0.0, 0.0);
    grid_pyramid.pos      = glm::vec3(0.0, grid_range / 2.0, 0.0);
    grid_pyramid.scale    = glm::vec3(0.02, 0.02, 0.04);
    model                 = grid_pyramid.GetModelMatrix();
    grid_pyramid.shader->Use();
    grid_pyramid.shader->SetMat4f("model", model);
    grid_pyramid.shader->Set3f("mycol", mycolor.x, mycolor.y, mycolor.z);
    grid_pyramid.Draw();

    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
}

void Coord::CameraUpdate(glm::mat4& render_mat) {
    grid_shader->Use();
    grid_shader->SetMat4f("renderMat", render_mat);
    color_shader->Use();
    color_shader->SetMat4f("renderMat", render_mat);
}