#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
  public:
    int cam_width;
    int cam_height;

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    float lastX;      // Last position of mouse X.
    float lastY;      // Last position of mouse Y.
    float yaw;        // Rotation of angle z-axis.
    float pitch;      // Rotation of angle y-axis.
    float roll;       // [locked] Rotation of angle x-axis.
    bool  firstMouse; // Whether first move into screen.
    float speed;      // mouse position move speed.
    float sensity;    // mouse angle move speed.
    float zoom;       // vesion angle.

    float deltaTime; // last and current frame's delta time.
    float lastFrame; // record last frame render time.

    // control int 3Dview.
    glm::vec2 st;           // start position.
    glm::vec2 end;          // end position.
    glm::vec2 mouse_pos;    // mouse position.
    bool      ctrl_pressed; // whether crrl is pressed.

    Camera();

    ~Camera();

    void RotateHorizontal(float time_tick);

    glm::mat4 GetViewMatrix();

    glm::mat4 GetProjectMatrix(int w_width, int w_height);

    glm::mat4 GetRenderMatrix(int w_width, int w_height);

    void ProcessInput(GLFWwindow* window);

    void mouse_click_callback(GLFWwindow* window, int button, int action, int mode);

    void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    bool InRange();
};
