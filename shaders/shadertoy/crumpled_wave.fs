#version 330 core

out vec4 fragColor;
in vec2  coord_im;

uniform sampler2D textureid;
uniform float iTime;

vec2 fragCoord   = coord_im.xy;
vec2 iResolution = vec2(1.0, 1.0);

void main(){
    vec2 uv =  (2.0 * fragCoord - iResolution.xy) / min(iResolution.x, iResolution.y);
   
    for(float i = 1.0; i < 8.0; i++){
    uv.y += i * 0.1 / i * 
      sin(uv.x * i * i + iTime * 0.5) * sin(uv.y * i * i + iTime * 0.5);
  }
    
   vec3 col;
   col.r  = uv.y - 0.1;
   col.g = uv.y + 0.3;
   col.b = uv.y + 0.95;
    
    fragColor = vec4(col,1.0);
}