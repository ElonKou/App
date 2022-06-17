#pragma once

#include "RayTracingCore.hh"
#include "WindowBase.hh"

class RayTracingControlWindow : WindowBase {
  public:
    std::shared_ptr<RayTracingCore> core;

    RayTracingControlWindow();

    ~RayTracingControlWindow();

    virtual void Show() override;
};
