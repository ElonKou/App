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
#include <cmath>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

using namespace cpptypes;

class Base {
  public:
    Base() {}

    ~Base() {}
};

// extern class Application* app; // viewport of openGL window.

#endif