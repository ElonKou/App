#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 col;

uniform vec3 offset;
uniform float scale;

out vec3 ourColor;

void main() {
    gl_Position = vec4(pos + offset * 0.05, 1.0f);
    gl_Position.x = gl_Position.x * scale;
    gl_Position.y = gl_Position.y * scale;
    ourColor    = col + offset;
}