#version 400

layout (location = 0) in vec3 inPos;

out vec2 texCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    vec3 normal = normalize(inPos);
    Normal = mat3(transpose(inverse(modelMatrix))) * normal;
    
    float s = atan(normal.x, normal.z) / 3.141592 + 0.5;
    float t = normal.y * 0.5 + 0.5;
    texCoord = vec2(s, t);
    
    FragPos = vec3(modelMatrix * vec4(inPos, 1.0));
    gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0);
}