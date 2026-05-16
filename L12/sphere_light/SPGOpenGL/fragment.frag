#version 400

out vec4 FragColor;

in vec2 texCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D noiseTex;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float delta;

vec2 noiseGradient(vec2 coords, float delta) {
    float sample1x = texture(noiseTex, vec2(coords.s + delta, coords.t)).r;
    float sample2x = texture(noiseTex, vec2(coords.s - delta, coords.t)).r;
    
    float sample1y = texture(noiseTex, vec2(coords.s, coords.t + delta)).r;
    float sample2y = texture(noiseTex, vec2(coords.s, coords.t - delta)).r;
    
    return vec2(sample1x - sample2x, sample1y - sample2y);
}

void main() {
    vec3 normal = normalize(Normal);
    
    normal.xy += noiseGradient(texCoord, delta);
    normal = normalize(normal);

    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 objectColor = vec3(0.0, 0.8, 0.2); 

    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}