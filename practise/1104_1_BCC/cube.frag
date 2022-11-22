#version 330 core
out vec4 FragColor;

// 在这里也定义了材质，同时将纹理当作了材质的一部分
struct Material {
    sampler2D texture;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
};
// 表示光源，里面有位置和颜色两个信息
struct Light {
    vec3 position;
    vec3 color;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos; // 表示视角的位置，用来计算镜面反射的
uniform Material material;
uniform Light light;

void main()
{
    // ambient
    float ambient = material.ambient;

    // diffuse 光照射到物体的角度越小，物体就会越暗。
    vec3 norm = normalize(Normal); // 法向向量
    vec3 lightDir = normalize(light.position - FragPos); // 指向光源的向量
    float diff = max(dot(norm, lightDir), 0.0); // 点乘
    float diffuse = material.diffuse * diff; // 和材质中的diffuse值进行相乘

    // specular 镜面反射：只有diff的计算大于0的时候才计算镜面。
    float spec = 0;
    if (diff > 0)
    { // 如果光都没有照射到物体表面，那就不需要计算镜面反射了。
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    }
    float specular = material.specular * spec;

    // final
    vec3 result = (ambient + diffuse) * texture(material.texture, TexCoords).rgb * light.color
        + specular * light.color;

    FragColor = vec4(result, 1.0);
}
