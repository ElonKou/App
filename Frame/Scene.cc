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
    texture    = new Texture(APP_RESOURCES_PATH "/images/gESgL.jpeg");
    texture->Bind();

    // Coord init.
    coord.Init();
}

Scene::~Scene() {
    if (texture) {
        delete texture;
    }
    if (shader) {
        delete shader;
    }
}

void Scene::AddObj(Mesh* obj) {
    if (!obj->texture) {
        obj->texture = texture;
    }
    if (!obj->shader) {
        obj->shader = shader;
    }
    obj->Init();
    objs.push_back(obj);
}

void Scene::CameraUpdate(Camera &cam) {
    glm::mat4 render = cam.GetRenderMatrix(cam.cam_width, cam.cam_height);
    coord.CameraUpdate(render);
}

void Scene::Draw(Camera &cam) {
    for (size_t i = 0; i < objs.size(); i++) {
        glm::mat4 model = objs[i]->GetModelMatrix();
        if (!objs[i]->shader) {
            objs[i]->shader = shader;
        }
        objs[i]->shader->Use();
        glm::mat4 render = cam.GetRenderMatrix(cam.cam_width, cam.cam_height);
        objs[i]->shader->SetMat4f("renderMat", render);
        objs[i]->shader->SetMat4f("model", model);
        if (objs[i]->texture) {
            // set texture id for every shader according its shader id.
            objs[i]->texture->Bind();
            objs[i]->shader->Set1i("textureid", objs[i]->texture->cur_id);
        }
        objs[i]->Draw();
    }
    if (draw_coord) {
        coord.Draw();
    }
}
