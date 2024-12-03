#version 330 core

in vec4 vertex;  
in vec2 uv0;     

uniform mat4 modelViewProjMat;
uniform float sintime;

out vec2 vUv0; 
out float zf;   // Valor de zoom
out float tiempo; 

void main() {
    // Calcular valor de zoom basado en sintime [0.75, 1.25]
    float ZF = sintime * 0.25 + 1.0;

    // Modificar coordenadas de textura para aplicar zoom
    vec2 uvCentered = uv0 - vec2(0.5, 0.5); 
    uvCentered *= ZF;  // Aplicar zoom
    vUv0 = uvCentered + vec2(0.5, 0.5); 

    // Pasar valores al fragment shader
    zf = ZF;
    tiempo = sintime;

    // Transformar la posición del vértice
    gl_Position = modelViewProjMat * vertex;
}
