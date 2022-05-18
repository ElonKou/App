#version 330 core

out vec4 color;
in vec2  coord_im;

uniform sampler2D textureid;
uniform float iTime;

vec2 fragCoord   = coord_im.xy;
vec2 iResolution = vec2(1.0, 1.0);

#define F +texture(textureid, .3 + p.xz * s / 3e3) / (s += s)

void main() {
    vec4 p = vec4(fragCoord / iResolution.xy, 1, 1) - .5, d = p, t;
    p.z += iTime * 20.;
    d.y -= .4;

    for (float i = 1.5; i > 0.; i -= 0.003) {
        float         s = .5;
        t               = F F F F;
        color           = 1. + d.x - t * i;
        color.z -= .1;
        if (t.x > p.y * .007 + 1.3)
            break;
        p += d;
    }
}