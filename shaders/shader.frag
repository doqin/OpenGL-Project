#version 330 core
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {
    // Calculate the ambient light
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Calculate the diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    // dot of two normalized vectors give cos(theta) (theta is the angle between the two vectors)
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Calculate the specular light
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128); // 32 is the shininess of the highlight
    vec3 specular = specularStrength * spec * lightColor;

    vec3 lighting = ambient + diffuse + specular;
    vec4 texColor = texture(ourTexture, TexCoord);
    vec4 result = texColor * vec4(lighting, 1.0);

    FragColor = result;
}
