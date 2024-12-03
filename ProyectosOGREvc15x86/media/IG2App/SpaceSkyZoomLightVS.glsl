#version 330 core
in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjMat;
uniform float sintime; 
out vec2 vUv0;
out float zf;
out float tiempo;

void main() {
    float ZF = sintime * 0.25 + 1.0;
    vec2 uvCentered = uv0 - vec2(0.5, 0.5);
    uvCentered *= ZF;
    vUv0 = uvCentered + vec2(0.5, 0.5);
    zf = ZF;
    tiempo = sintime;
    gl_Position = modelViewProjMat * vertex;
}