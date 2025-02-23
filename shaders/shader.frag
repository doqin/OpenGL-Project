#version 330 core

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
};

struct Material {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

void main() {

    // Calculate the ambient light
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

    // Calculate the diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.position - FragPos);
    // vec3 lightDir = normalize(-light.direction);
    // dot of two normalized vectors give cos(theta) (theta is the angle between the two vectors)
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

    // Calculate the specular light
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // 32 is the shininess of the highlight
    vec3 specular = light.specular * (spec * material.specular);

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // ambient *= attenuation;
    // diffuse *= attenuation;
    // specular *= attenuation;

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    diffuse *= intensity;
    specular *= intensity;

    vec3 lighting;
    lighting = ambient + diffuse + specular;
    vec4 result = vec4(lighting, 1.0);

    FragColor = result;
}
