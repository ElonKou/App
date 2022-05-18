#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 coord;

uniform mat4 model;
uniform mat4 renderMat;

void main() {
    gl_Position = renderMat * model * vec4(position, 1.0);
}