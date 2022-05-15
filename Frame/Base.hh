#pragma once
#ifndef BASE_HH_
#define BASE_HH_

#include "../3rdparty/cppbase/cpptools.hpp"
#include "../3rdparty/cppbase/cpptypes.hpp"
#include "imgui.h"
#include "../3rdparty/imgui/imgui_app_extension.h"
#include "../3rdparty/imgui/imgui_app_tools.h"
#include "../3rdparty/imgui/imgui_app_widgets.h"
#include "../3rdparty/imgui/imgui_impl_glfw.h"
#include "../3rdparty/imgui/imgui_impl_opengl3.h"
#include "../3rdparty/imgui/imgui_internal.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "AppConfig.hh"

using namespace cpptypes;

class Base {
  public:
    Base() {}

    ~Base() {}
};

extern class MainViewport* viewport; // viewport of openGL window.

#endif