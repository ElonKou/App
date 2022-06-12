/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : Scene.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Mon Feb  7 16:51:06 2022
================================================================*/

#include "Scene.hh"

Scene::Scene() {
    draw_coord = true;
    shader     = new Shader({APP_SHADERS_PATH "/demo_vertex.vs", APP_SHADERS_PATH "/demo_frag.fs"});
    texture    = new Texture("gESgL.jpeg", APP_RESOURCES_PATH "/images");

    cam = std::make_shared<Camera>();

    // Coord init.
    coord.Init();

    our_shader = std::make_shared<Shader>(APP_SHADERS_PATH "/model_loading.vs", APP_SHADERS_PATH "/model_loading.fs");
    our_model  = std::make_shared<Model>(APP_RESOURCES_PATH "/backpack/backpack.obj");
}

Scene::~Scene() {
    if (texture) {
        delete texture;
    }
    if (shader) {
        delete shader;
    }
}

void Scene::AddObj(iMesh* obj) {
    if (!obj->texture) {
        obj->texture = texture;
    }
    if (!obj->shader) {
        obj->shader = shader;
    }
    obj->Init();
    objs.push_back(obj);
}

void Scene::Draw() {
    glm::mat4 render = cam->GetRenderMatrix(cam->cam_width, cam->cam_height);
    for (size_t i = 0; i < objs.size(); i++) {
        glm::mat4 model = objs[i]->GetModelMatrix();
        if (!objs[i]->shader) {
            objs[i]->shader = shader;
        }
        objs[i]->shader->Use();
        objs[i]->shader->SetMat4f("renderMat", render);
        objs[i]->shader->SetMat4f("model", model);
        if (objs[i]->texture) {
            // set texture id for every shader according its shader id.
            objs[i]->texture->Bind();
            objs[i]->shader->Set1i("textureid", objs[i]->texture->id);
        }
        objs[i]->Draw();
    }
    if (draw_coord) {
        coord.CameraUpdate(render);
        coord.Draw();
    }
    {
        our_shader->Use();

        // view/projection transformations
        glm::mat4 model = glm::mat4(1.0f);
        our_shader->SetMat4f("renderMat", render);
        our_shader->SetMat4f("model", model);

        // render the loaded model
        our_model->Draw(*our_shader.get());
    }
}

void Scene::ProcessInput(GLFWwindow* window) {
    cam->ProcessInput(window);
}