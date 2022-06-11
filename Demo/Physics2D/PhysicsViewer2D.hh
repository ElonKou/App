#pragma once

#include "Physics2D.hh"
#include "PhysicsScene2D.hh"
#include "WindowBase.hh"

class PhysicsViewer2D : public WindowBase {
  public:
    std::shared_ptr<Physics2D>      phy;   // pointer to physics2D objects.
    std::shared_ptr<PhysicsScene2D> scene; // pointer to PhysicsScene2D objects.

    PhysicsViewer2D();

    ~PhysicsViewer2D();

    void Show();
};