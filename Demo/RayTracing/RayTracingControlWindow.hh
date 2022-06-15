#pragma once

#include "SimpleImage.hh"
#include "WindowBase.hh"

class RayTracingControlWindow : WindowBase {
  public:
    std::shared_ptr<SimpleImage> img;

    RayTracingControlWindow();

    ~RayTracingControlWindow();

    virtual void Show() override;
};
