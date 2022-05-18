#pragma once

#include "Coord.hh"
#include "Mesh.hh"
#include "Shader.hh"
#include "Texture.hh"
#include "Window.hh"

class Scene {
  public:
    Texture*           texture; // default Txxture;
    Shader*            shader;  // store the render shader.
    std::vector<Mesh*> objs;    // contains all Mesh objects.
    Coord              coord;   // Coord with axis.

    bool draw_coord; // whether draw coord.

    Scene();

    ~Scene();

    /**
     * add mesh obj into Scene list, and init.
     */
    void AddObj(Mesh* obj);

    void CameraUpdate(Camera& cam); // check camera update.

    void Draw(Camera& cam);
};
