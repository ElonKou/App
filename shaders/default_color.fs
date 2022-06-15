#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 VexColor;

uniform sampler2D texture_diffuse1;

void main() {
    FragColor = vec4(VexColor, 1.0f);
}