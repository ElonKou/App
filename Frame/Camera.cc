/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : Camera.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Sat Feb  5 16:05:08 2022
================================================================*/

#include "Camera.hh"
#include <iostream>

Camera::Camera() {
    cam_width  = 800;
    cam_height = 600;

    cameraPos   = glm::vec3(0.0f, 0.0f, 5.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

    // Default FPS camera values
    yaw     = -90.0f;
    pitch   = 0.0f;
    speed   = 2.0f;
    sensity = 0.06f;
    zoom    = 45.0f;

    deltaTime  = 0.0f; // last and current frame's delta time.
    lastFrame  = 0.0f; // record last frame render time.
    firstMouse = true;
}

Camera::~Camera() {
}

void Camera::RotateHorizontal(float time_tick) {
    float radius = 10.0f;
    float camX   = sin(time_tick) * radius;
    float camZ   = cos(time_tick) * radius;
    cameraPos    = glm::vec3(camX, 0.0f, camZ);
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::mat4 Camera::GetProjectMatrix(int w_width, int w_height) {
    return glm::perspective(glm::radians(zoom), (float)w_width / (float)w_height, 0.1f, 1000.0f);
}

glm::mat4 Camera::GetRenderMatrix(int w_width, int w_height) {
    return GetProjectMatrix(w_width, w_height) * GetViewMatrix();
}

void Camera::ProcessInput(GLFWwindow* window) {
    float currentFrame = glfwGetTime();
    deltaTime          = currentFrame - lastFrame;
    lastFrame          = currentFrame;
    float cameraSpeed  = speed * deltaTime; // adjust the view's move speed.

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        cameraPos.y += cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        cameraPos.y -= cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
}

void Camera::mouse_click_callback(GLFWwindow* window, int button, int action, int mode) {
    // click
    std::cout << "button: " << button << " acction: " << action << " mode: " << mode << std::endl;
}

void Camera::mouse_move_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX      = xpos;
        lastY      = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX         = xpos;
    lastY         = ypos;

    xoffset = xoffset * sensity;
    yoffset = yoffset * sensity;

    yaw   = yaw + xoffset;
    pitch = pitch + yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x     = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y     = sin(glm::radians(pitch));
    front.z     = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    zoom -= (float)yoffset;
    if (zoom < 1.0f) {
        zoom = 1.0f;
    }
    if (zoom > 150.0f) {
        zoom = 150.0f;
    }
}