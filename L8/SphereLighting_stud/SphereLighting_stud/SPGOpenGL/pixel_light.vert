#version 400
layout(location = 0) in vec3 vPos;

uniform mat4 mvpMatrix;
uniform mat4 normalMatrix;

out vec3 normal;
out vec3 pos;

void main() 
{
	gl_Position = mvpMatrix * vec4(vPos, 1.0);
	
	vec3 computedNormal = normalize(vPos);

	normal = mat3(normalMatrix) * computedNormal;
	
	pos = vPos;
}