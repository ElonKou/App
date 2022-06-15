#version 330 core

in vec3 ourColor;
in vec2 TexCoord;
out vec4 color;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main() {
    // only use one texture.
    // color = texture(ourTexture2, TexCoord);
    color = mix(texture(ourTexture2, TexCoord), texture(ourTexture1, TexCoord), 0.5);
    color = mix(color, vec4(ourColor, 1.0f), 0.3);
    color = color.xyzx * color.yzxx * 1.5;
}
