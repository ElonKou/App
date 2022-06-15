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

    std::shared_ptr<Shader> default_texture_shader; // shader with texture.
    std::shared_ptr<Shader> default_color_shader;   // color shader for render use color.
    std::shared_ptr<Shader> default_shader;         // default sahder.

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
