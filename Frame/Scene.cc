/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : Scene.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Mon Feb  7 16:51:06 2022
================================================================*/

#include "Scene.hh"

Scene::Scene() {
    draw_coord             = true;
    cam                    = std::make_shared<Camera>();
    default_texture_shader = std::make_shared<Shader>(APP_SHADERS_PATH "/default.vs", APP_SHADERS_PATH "/default.fs");
    default_color_shader   = std::make_shared<Shader>(APP_SHADERS_PATH "/default_color.vs", APP_SHADERS_PATH "/default_color.fs");
    default_shader         = default_texture_shader;
}

Scene::~Scene() {}

void Scene::Draw() {
    glm::mat4 render = cam->GetRenderMatrix(cam->cam_width, cam->cam_height);
    // draw all Mesh objects.
    for (size_t i = 0; i < objs.size(); i++) {
        glm::mat4 model = objs[i]->GetModelMatrix();
        if (objs[i]->textures.size() < 1) {
            default_shader = default_color_shader;
        } else {
            default_shader = default_texture_shader;
        }
        default_shader->Use();
        default_shader->SetMat4f("renderMat", render);
        default_shader->SetMat4f("model", model);
        objs[i]->Draw(*default_shader.get());
    }
    // draw all Models.
    for (size_t i = 0; i < models.size(); i++) {
        for (size_t j = 0; j < models[i]->meshes.size(); j++) {
            glm::mat4 model = models[i]->meshes[j].GetModelMatrix();
            if (models[i]->textures_loaded.size() < 1) {
                default_shader = default_color_shader;
            } else {
                default_shader = default_texture_shader;
            }
            default_shader->Use();
            default_shader->SetMat4f("renderMat", render);
            default_shader->SetMat4f("model", model);
            models[i]->meshes[j].Draw(*default_shader.get()); // render the loaded model
        }
    }
    // draw coord.
    if (draw_coord) {
        coord.CameraUpdate(render);
        coord.Draw();
    }
}

void Scene::ProcessInput(GLFWwindow* window) {
    cam->ProcessInput(window);
}