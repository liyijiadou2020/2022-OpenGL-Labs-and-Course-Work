#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform float utime;

in vec3 gFragPos;
in vec3 gNormal;
in vec2 gTexCoords;

out vec3 fFragPos;
out vec3 fNormal;
out vec2 fTexCoords;


void main() {
    // gl_in是前一个着色器阶段的输出
    gl_Position = gl_in[0].gl_Position + vec4( 0.0, 0.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + vec4( 0.0, 0.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[2].gl_Position + vec4( 0.0, 0.0, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();

    fFragPos = gFragPos;
    fNormal = gNormal; // #TODO 生成新的法向量
    fTexCoords = gTexCoords;

}
