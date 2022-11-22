#version 330
uniform mat4 uPMatrix,camMatrix,uMMatrix;
layout (location = 0) in vec3 aPosition;
smooth out vec3 vPosition;

void main(void)
{
    gl_Position = uPMatrix * camMatrix *uMMatrix * vec4(aPosition,1);
    vPosition = aPosition;
}
