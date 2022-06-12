/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : Scene.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Mon Feb  7 16:51:06 2022
================================================================*/

#include "Scene.hh"

Scene::Scene() {
    draw_coord     = true;
    cam            = std::make_shared<Camera>();
    deafult_shader = std::make_shared<Shader>(APP_SHADERS_PATH "/default.vs", APP_SHADERS_PATH "/default.fs");
}

Scene::~Scene() {}

void Scene::Draw() {
    glm::mat4 render = cam->GetRenderMatrix(cam->cam_width, cam->cam_height);
    // draw all Mesh objects.
    for (size_t i = 0; i < objs.size(); i++) {
        glm::mat4 model = objs[i]->GetModelMatrix();
        deafult_shader->Use();
        deafult_shader->SetMat4f("renderMat", render);
        deafult_shader->SetMat4f("model", model);
        objs[i]->Draw(*deafult_shader.get());
    }
    // draw all Models.
    for (size_t i = 0; i < models.size(); i++) {
        glm::mat4 model = glm::mat4(1.0f);
        deafult_shader->Use();
        deafult_shader->SetMat4f("renderMat", render);
        deafult_shader->SetMat4f("model", model);
        models[i]->Draw(*deafult_shader.get()); // render the loaded model
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