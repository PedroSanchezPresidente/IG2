#version 330 core
in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjMat;
uniform float time; 
uniform vec4 centro;
uniform float amplitud1;
uniform float amplitud2;
out vec2 vUv0;

void main() {
    vUv0 = uv0;
    vec4 vertexCoord = vertex;
     float distanceCenter = length(vertex.xyz - centro.xyz);
    vertexCoord.y += sin(vertexCoord.x + (time*0.25)) * amplitud1 + sin(vertexCoord.z + (distanceCenter) + (time*25)) * amplitud2; 
    gl_Position = modelViewProjMat * vertexCoord;
}
