/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : Shader.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Sat 18 Apr 2020 12:14:50 AM CST
================================================================*/

#include "Shader.hh"

void Shader::CheckCompileShader(GLuint& shader) {
    GLint succes;
    char  infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
    if (!succes) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILED_FAILED" << std::endl
                  << infoLog << std::endl;
    }
}

void Shader::CheckLinkProgram(GLuint program) {
    GLint succes;
    char  infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &succes);
    if (!succes) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED" << std::endl
                  << infoLog << std::endl;
    }
}

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
    std::ifstream vShaderFile;  // shader file.
    std::ifstream fShaderFile;  // sahder file.
    std::string   vertexCode;   // shader content.
    std::string   fragmentCode; // shader content.

    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        if (!vShaderFile) {
            std::cout << "ERROR::SHADER::FAIL_NOT_FOUND_SHADER_PATH " << vertexPath << std::endl;
        }
        if (!fShaderFile) {
            std::cout << "ERROR::SHADER::FAIL_NOT_FOUND_SHADER_PATH " << fragmentPath << std::endl;
        }
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FAIL_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const GLchar* vertexCodes   = vertexCode.c_str();
    const GLchar* fragmentCodes = fragmentCode.c_str();
    GLuint        vertexShader, fragmentShader;
    // vertexShader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCodes, NULL); // copy shader content into shader object.
    glCompileShader(vertexShader);                       // compile shader
    CheckCompileShader(vertexShader);
    // fragmentShader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCodes, NULL);
    glCompileShader(fragmentShader);
    CheckCompileShader(fragmentShader);
    // shaderProgram
    Program = glCreateProgram();
    glAttachShader(Program, vertexShader);   // attach shader.
    glAttachShader(Program, fragmentShader); // attach shader.
    glLinkProgram(Program);                  // Linke progrma.
    CheckLinkProgram(Program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Use() {
    glUseProgram(Program);
}

void Shader::Print() {
    std::cout << vertexCode << fragmentCode;
}

void Shader::Set1i(const std::string& name, int v) {
    glUniform1i(glGetUniformLocation(Program, name.c_str()), v);
}

void Shader::Set1f(const std::string& name, float v) {
    glUniform1f(glGetUniformLocation(Program, name.c_str()), v);
}

void Shader::Set2i(const std::string& name, int v1, int v2) {
    glUniform2i(glGetUniformLocation(Program, name.c_str()), v1, v2);
}

void Shader::Set2f(const std::string& name, float v1, float v2) {
    glUniform2f(glGetUniformLocation(Program, name.c_str()), v1, v2);
}
void Shader::Set3i(const std::string& name, int v1, int v2, int v3) {
    glUniform3i(glGetUniformLocation(Program, name.c_str()), v1, v2, v3);
}

void Shader::Set3f(const std::string& name, float v1, float v2, float v3) {
    glUniform3f(glGetUniformLocation(Program, name.c_str()), v1, v2, v3);
}
void Shader::Set4i(const std::string& name, int v1, int v2, int v3, int v4) {
    glUniform4i(glGetUniformLocation(Program, name.c_str()), v1, v2, v3, v4);
}

void Shader::Set4f(const std::string& name, float v1, float v2, float v3, float v4) {
    glUniform4f(glGetUniformLocation(Program, name.c_str()), v1, v2, v3, v4);
}

void Shader::SetMat4f(const std::string& name, glm::mat4 mat) {
    glUniformMatrix4fv(glGetUniformLocation(Program, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}