#version 330 core

in vec4 vertexColor;

out vec4 color;

uniform vec4 ourColor;

void main() {
    // color = vec4(1.0f, 1.0f, 0.0f, 1.0f);
    color = vertexColor;
    if (abs(color.x) < 0.002) {
        color = vec4(1.0, 1.0, 0.0, 1.0f);
    }
    if (abs(color.y) < 0.002) {
        color = vec4(1.0, 0.3, 0.8, 1.0f);
    }
}