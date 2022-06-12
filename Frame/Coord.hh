#pragma once

#include "Mesh.hh"
#include "Shader.hh"

class Coord {
  private:
    int   grid_cnt;  // subdivisions of grid.
    float grid_size; // grid size.

    Shader* grid_shader;  // render for grid.
    Shader* color_shader; // render for axis.
    Mesh    grid_plane_x;
    Mesh    grid_plane_y;
    Mesh    grid_plane_z;
    Mesh    grid_box;
    Mesh    grid_pyramid;

  public:
    float grid_range; // grid range default = 1.0.

    Coord();

    ~Coord();

    void Draw();

    void CameraUpdate(glm::mat4& render_mat);
};
