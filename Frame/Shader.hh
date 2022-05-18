#pragma once
#ifndef SHADER_CLASS_H_
#define SHADER_CLASS_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
  private:
    void CheckCompileShader(GLuint& shader);

    void CheckLinkProgram(GLuint program);

  public:
    std::string vertexCode;
    std::string fragmentCode;
    GLuint      Program;

    Shader() {}

    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    void Use();

    void Print();

    void Set1i(const std::string& name, int v);

    void Set1f(const std::string& name, float v);

    void Set2i(const std::string& name, int v1, int v2);

    void Set2f(const std::string& name, float v1, float v2);

    void Set3i(const std::string& name, int v1, int v2, int v3);

    void Set3f(const std::string& name, float v1, float v2, float v3);

    void Set4i(const std::string& name, int v1, int v2, int v3, int v4);

    void Set4f(const std::string& name, float v1, float v2, float v3, float v4);

    void SetMat4f(const std::string& name, glm::mat4 mat);
};
#endif