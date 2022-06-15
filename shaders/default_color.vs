#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in vec3 aColor;

out vec2 TexCoords;
out vec3 VexColor;

uniform mat4 model;
uniform mat4 renderMat;

void main() {
    TexCoords   = aTexCoords;
    VexColor    = aColor;
    gl_Position = renderMat * model * vec4(aPos, 1.0);
}