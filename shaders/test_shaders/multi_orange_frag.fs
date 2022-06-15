#version 330 core

out vec4 color;

uniform vec4 ourColor;

void main() {
    color = ourColor + vec4(0.12f, 0.0f, 0.2f, 1.0f);
}