#version 430
in vec3 vPosition;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main(void)
{
    gl_Position=proj_matrix*mv_matrix*vec4(vPosition,1.0);
}
