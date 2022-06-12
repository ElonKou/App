#pragma once

#include "Camera.hh"
#include "Coord.hh"
#include "Model.hh"
#include "Shader.hh"
#include "Texture.hh"
#include "Window.hh"
#include "iMesh.hh"

class Scene {
  public:
    Texture*            texture; // default texture.
    Shader*             shader;  // store the render shader.
    std::vector<iMesh*> objs;    // contains all iMesh objects.
    Coord               coord;   // Coord with axis.

    std::shared_ptr<Camera> cam; // 3D camera.

    bool draw_coord; // whether draw coord.

    std::shared_ptr<Model>  our_model;
    std::shared_ptr<Shader> our_shader;

    Scene();

    ~Scene();

    /**
     * add mesh obj into Scene list, and init.
     */
    void AddObj(iMesh* obj);

    void Draw();

    void ProcessInput(GLFWwindow* window);
};
