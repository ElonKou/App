#pragma once
#ifndef BASE_HH_
#define BASE_HH_

#include "AppConfig.hh"
#include "cpptools.hpp"
#include "cpptypes.hpp"
#include "imgui.h"
#include "imgui_app_extension.h"
#include "imgui_app_tools.h"
#include "imgui_app_widgets.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>
#include <memory>

using namespace cpptypes;

class Base {
  public:
    Base() {}

    ~Base() {}
};

// extern class Application* app; // viewport of openGL window.

#endif