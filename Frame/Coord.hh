#pragma once

#include "iMesh.hh"
#include "Shader.hh"

class Coord {
  private:
    int   grid_cnt;  // subdivisions of grid.
    float grid_size; // grid size.

    Shader* grid_shader;  // render for grid.
    Shader* color_shader; // render for axis.
    iMesh    grid_plane_x;
    iMesh    grid_plane_y;
    iMesh    grid_plane_z;
    iMesh    grid_box;
    iMesh    grid_pyramid;

  public:
    float grid_range; // grid range default = 1.0.

    Coord();

    ~Coord();

    void Init();

    void Draw();

    void CameraUpdate(glm::mat4& render_mat);
};
