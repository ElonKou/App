#version 330 core

out vec4 color;

uniform vec3 mycol;

void main() {
    color = vec4(mycol, 1.0f);
}