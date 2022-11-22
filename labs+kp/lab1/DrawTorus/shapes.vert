#version 330
uniform mat4 uPMatrix, uVMatrix, uMMatrix;
layout (location = 0)in vec3 aPosition;
layout (location = 1)in vec4 aColor;
smooth out vec4 vColor;

void main(void)
{
    gl_Position = uPMatrix * uVMatrix * uMMatrix * vec4(aPosition,1);
    vColor = aColor;
}
