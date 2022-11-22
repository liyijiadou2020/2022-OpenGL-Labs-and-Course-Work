#version 330 core
// 这里有一个三维向量的输入，名字vPos是我们自己定义的。
// 在我们需要向解释OpenGL如何解析数据的时候，我们通过shader来设置这个vPos的值
in vec3 vPos;
/* 纹理 */
in vec2 vTexture;
out vec2 oTexture;
/* 摄像机 */
// 投影矩阵（projection），视图矩阵（view）和模型矩阵（model）
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    //gl_Position表示最终输出的位置，内置的，不需要我们定义
    gl_Position = projection * view * model * vec4(vPos, 1.0);
    oTexture = vTexture;
}
