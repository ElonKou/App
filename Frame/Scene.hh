#pragma once

#include "Camera.hh"
#include "Coord.hh"
#include "Model.hh"
#include "Shader.hh"
#include "Texture.hh"
#include "Window.hh"

class Scene {
  public:
    std::vector<Mesh*>      objs;       // contains all Mesh objects.
    std::vector<Model*>     models;     // contains all models.
    std::shared_ptr<Camera> cam;        // 3D camera.
    Coord                   coord;      // Coord with axis.
    bool                    draw_coord; // whether draw coord.

    std::shared_ptr<Shader> deafult_shader;

    Scene();

    ~Scene();

    /**
     * add mesh obj into Scene list, and init.
     */
    void AddMesh(Mesh* obj) { objs.push_back(obj); }

    void AddModel(Model* model) { models.push_back(model); }

    void Draw();

    void ProcessInput(GLFWwindow* window);
};
