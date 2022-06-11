#pragma once

#include "Application.hh"
#include "Physics2D.hh"
#include "PhysicsViewer2D.hh"

class PhysicsDemo2D : public Application {
  public:
    std::shared_ptr<Physics2D>       phy;    // physics 2D
    std::shared_ptr<PhysicsViewer2D> viewer; // Physics viewer.
    std::shared_ptr<PhysicsScene2D>  scene;  // physics scene.

    PhysicsDemo2D();

    ~PhysicsDemo2D();

    virtual void InitApp() override;

    virtual void UpdateApp() override;
};
