/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : demo.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Mon Feb  7 17:19:58 2022
================================================================*/

#include "iMesh.hh"
#include "Scene.hh"
#include "Window.hh"

int xx(int argc, char* argv[]) {
    Window window;
    Scene  scene;
    iMesh   box     = GetBox();
    iMesh   planeA  = GetRectWithCoord();
    iMesh   planeB  = GetRectWithCoord();
    iMesh   planeC  = GetRectWithCoord();
    iMesh   ptramid = GetPyramid();

    glm::vec3 positions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};

    scene.AddObj(&box);
    scene.AddObj(&planeA);
    scene.AddObj(&planeB);
    scene.AddObj(&planeC);
    scene.AddObj(&ptramid);

    while (!window.Closed()) {
        window.Clear();
        scene.cam->ProcessInput(window.window);
        scene.ProcessInput(window.window);

        planeA.scale    = glm::vec3(1.0f);
        planeB.scale    = glm::vec3(1.0f);
        planeC.scale    = glm::vec3(1.0f);
        planeB.rotation = glm::vec3(glm::radians(90.0), 0.0, 0.0);
        planeC.rotation = glm::vec3(0.0, glm::radians(90.0), 0.0);
        box.scale       = glm::vec3(0.1);
        box.rotation.x  = glfwGetTime();
        box.rotation.y  = glfwGetTime();
        ptramid.pos     = positions[2];

        scene.Draw();

        window.Swap();
        window.PollEvents();
    }
    window.Terminate();

    return 0;
}
