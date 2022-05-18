#version 330 core

out vec4 fragColor;
in vec2  coord_im;

uniform sampler2D textureid;
uniform float     iTime;

vec2 fragCoord   = coord_im.xy;
vec2 iResolution = vec2(1.0, 1.0);

void main() {
    vec2 pos = 256.0 * fragCoord.xy / iResolution.x + iTime;
    vec3 col = vec3(0.0);
    for (int i = 0; i < 8; i++) {
        vec2 a = floor(pos);
        vec2 b = fract(pos);
        vec4 w = fract((sin(7.0 * a.x + 31.0 * a.y + 0.01 * iTime) + vec4(0.035, 0.01, 0.0, 0.7)) * 3.545317);
        col += w.xyz
               * smoothstep(0.45, 0.55, w.w)
               * sqrt(16.0 * b.x * b.y * (1.0 - b.y) * (1.0 - b.x));
        pos /= 2.0;
        col /= 2.0;
    }
    // col = pow(2.5*col, vec3(.7 + sin(iTime)* 0.4, 0.8 + cos(iTime) * 0.1, 0.9 - cos(iTime * 2.0) * 0.1));
    col       = pow(2.5 * col, vec3(1.0, 1.0, 0.7));
    fragColor = vec4(col, 1.0);
}