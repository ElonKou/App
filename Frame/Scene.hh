#pragma once

#include "Camera.hh"
#include "Coord.hh"
#include "Mesh.hh"
#include "Shader.hh"
#include "Texture.hh"
#include "Window.hh"

class Scene {
  public:
    Texture*           texture; // default texture.
    Shader*            shader;  // store the render shader.
    std::vector<Mesh*> objs;    // contains all Mesh objects.
    Coord              coord;   // Coord with axis.

    std::shared_ptr<Camera> cam; // 3D camera.

    bool draw_coord; // whether draw coord.

    Scene();

    ~Scene();

    /**
     * add mesh obj into Scene list, and init.
     */
    void AddObj(Mesh* obj);

    void Draw();

    void ProcessInput(GLFWwindow* window);
};
