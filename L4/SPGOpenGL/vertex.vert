#version 400
in vec3 vp;
uniform mat4 modelMatrix;
out vec3 position;
void main() {
	vec3 newPosition = vec3(vp.x * 0.5f , vp.y * 0.5f - 0.5f, vp.z);
	gl_Position = modelMatrix * vec4(newPosition, 1.0);
}