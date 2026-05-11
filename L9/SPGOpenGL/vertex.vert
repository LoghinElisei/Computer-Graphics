#version 400

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 normalMatrix;
uniform mat4 modelMatrix;

out vec3 normal;
out vec3 pos;

void main() 
{
	gl_Position = modelViewProjectionMatrix * vec4(vPos, 1.0);
	
	//normal = vNormal;
	//normal = vec3(normalMatrix * vec4(normal, 1));

	//pos = vPos;

	normal = vec3(normalMatrix * vec4(vNormal, 0.0));
	pos = vec3(modelMatrix * vec4(vPos, 1.0));


}