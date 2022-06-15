#version 330 core

in vec3 ourColor;
out vec4 color;

uniform vec3 offset;
vec3 tmp;

void main() {
    tmp = offset + ourColor;
    color = tmp.xyzx * tmp.yzxx * 10.0;
    // color = ourColor.xyzx * ourColor.yzxx * 10.0;
    color = 1 - color.xyzx * color.yzxy;
}
