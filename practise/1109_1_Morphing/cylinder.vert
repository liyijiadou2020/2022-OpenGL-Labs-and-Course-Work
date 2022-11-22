#version 330 core
in vec3 vPos;
in vec3 vNormal;

out vec3 gFragPos;
out vec3 gNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
//    FragPos就是指当前的顶点坐标，只进行了model的变化，不进行视图和投影变化
        gFragPos = vec3(model * vec4(vPos, 1.0));
        gNormal = mat3(transpose(inverse(model))) * vNormal;

        gl_Position = projection * view * model * vec4(vPos, 1.0);
}
