// Vertex Shader
#version 110

varying vec4 pos_sommet;
varying vec3 nml_sommet;

//varying mat3 nml_matrix;
//varying mat4 mv_matrix;

void main() {
    gl_Position  =  gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
    pos_sommet = gl_Vertex;
    nml_sommet = gl_Normal;
    //nml_matrix = gl_NormalMatrix;
    //mv_matrix  = gl_ModelViewMatrix;
}

