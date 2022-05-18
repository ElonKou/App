#version 330 core

in vec2  pos;
vec2     tmp;
out vec4 color;

uniform vec3 mycol;

float pi = 3.141592653;
float w  = 0.02;
int   n  = 11;

float splitRange(float x, float ma, float mb) {
    if (x < ma || x > mb) {
        return 0.0f;
    } else {
        return 1.0f;
    }
}

void main() {
    tmp = pos;

    tmp.xy = tmp.xy * (n - 1 + w * 2);
    if (n % 2 == 1) {
        tmp.xy = tmp.xy + 0.5 - w;
    }
    tmp.xy = fract(tmp.xy);
    tmp.x  = splitRange(tmp.x, 0.5 - w, 0.5 + w);
    tmp.y  = splitRange(tmp.y, 0.5 - w, 0.5 + w);

    if (tmp.x < 0.1 && tmp.y < 0.1) {
        color   = vec4(mycol, 1.0f);
        color.w = 0.05;
    } else {
        color   = vec4(mycol, 1.0f);
        color.w = 0.6;
    }
}