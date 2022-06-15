#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 col;

uniform vec3 offset;

out vec3 ourColor;

void main() {
    gl_Position = vec4(pos + offset, 1.0f);
    ourColor    = col + offset;
}