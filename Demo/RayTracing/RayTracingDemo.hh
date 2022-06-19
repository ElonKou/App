#pragma once

#include "Application.hh"
#include "RayDielectric.hh"
#include "RayLambertian.hh"
#include "RayMetal.hh"
#include "RaySphere.hh"
#include "RayTracingCamera.hh"
#include "RayTracingControlWindow.hh"
#include "RayTracingCore.hh"
#include "RayTracingScene.hh"
#include "RayTracingWindow.hh"
#include "SimpleImage.hh"

class RayTracingDemo : public Application {
  public:
    std::shared_ptr<RayTracingCamera>        cam;
    std::shared_ptr<SimpleImage>             img;
    std::shared_ptr<RayTracingCore>          core;
    std::shared_ptr<RayTracingControlWindow> cont;
    std::shared_ptr<RayTracingWindow>        disp;

    std::shared_ptr<RayTracingScene> scene;

    RayTracingDemo();

    ~RayTracingDemo();

    virtual void InitApp() override;

    virtual void UpdateApp() override;
};
