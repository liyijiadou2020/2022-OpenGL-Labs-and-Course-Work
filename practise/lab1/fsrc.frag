#version 330
uniform sampler2D sTextures;
in vec3 vPosition;
in vec4 vAmbient,vDiffuse,vSpecular;
in vec2 vTexture;
out vec4 fragColor;

void main(void)
{
    vec4 color = vec4(0.0,0.0,0.0,1.0);
    color = texture2D(sTextures,vTexture);
    fragColor = color * (vAmbient + vDiffuse + vSpecular);
}
