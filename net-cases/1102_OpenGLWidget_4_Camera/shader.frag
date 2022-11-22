#version 330 core
/* 纹理 */
in vec2 oTexture;
// uniform表示这个数据的来源可以是任何地方，包括CPU
// sampler2D：表示二维纹理
uniform sampler2D uTexture;

void main()
{
    // gl_FragColor 是表示最终输出的颜色，内置的，不需要我们定义，它是一个四维向量，即R，G，B，A。
//    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    // texture函数：将纹理指定位置映射到顶点上
    gl_FragColor = texture(uTexture, oTexture);

}
