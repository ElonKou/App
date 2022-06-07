#pragma once

#include "Camera.hh"
#include "FrameBuffer.hh"
#include "Scene.hh"
#include "WindowBase.hh"

class OpenGLWindow : public WindowBase {
  private:
    std::shared_ptr<Scene>       scene;
    std::shared_ptr<FrameBuffer> fbuffer;
    bool                         ret; // whether update.

  public:
    OpenGLWindow();

    ~OpenGLWindow();

    virtual void Show();

    inline void SetScene(std::shared_ptr<Scene> scene_) {
        scene = scene_;
    }
};
