#version 330 core
uniform sampler2D texturaL; 
uniform sampler2D texturaM;  
uniform float BF;            

uniform float minL;
uniform float maxL;

in vec2 vUv0;                
in float zf;                 
in float tiempo;

out vec4 fFragColor;         

void main() {
    vec3 colorL = vec3(texture(texturaL, vUv0));
    vec3 colorM = vec3(texture(texturaM, vUv0));

    vec3 color = mix(colorL, colorM, BF);

    float diff = maxL - minL;
    float lf = minL + (diff*((tiempo + 1) / 2));

    color *= zf * lf;

    fFragColor = vec4(color, 1.0);
}