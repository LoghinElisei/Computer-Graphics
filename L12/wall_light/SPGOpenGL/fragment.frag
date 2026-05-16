#version 400
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D diffuseMap;  
uniform sampler2D normalMapTex; 

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float mixFactor; 

void main()
{
    vec3 color = texture(diffuseMap, TexCoord).rgb;

    vec3 normalFromMap = texture(normalMapTex, TexCoord).rgb;
    
    normalFromMap.g = 1.0 - normalFromMap.g; 

    normalFromMap = normalize(normalFromMap * 2.0 - 1.0); 

    vec3 finalNormal = normalize(mix(Normal, normalFromMap, mixFactor)); 

    vec3 ambient = 0.2 * lightColor;
    
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(finalNormal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * color;
    FragColor = vec4(result, 1.0);
}