#pragma once

#include "Application.hh"
#include "RayTracingControlWindow.hh"
#include "RayTracingWindow.hh"
#include "SimpleImage.hh"

class RayTracingDemo : public Application {
  public:
    std::shared_ptr<RayTracingWindow>        disp;
    std::shared_ptr<RayTracingControlWindow> cont;
    std::shared_ptr<SimpleImage>             img;

    RayTracingDemo();

    ~RayTracingDemo();

    virtual void InitApp() override;

    virtual void UpdateApp() override;
};
