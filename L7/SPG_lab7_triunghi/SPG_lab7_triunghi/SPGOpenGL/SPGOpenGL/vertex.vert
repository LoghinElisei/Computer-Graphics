#version 400
///////// 1 ////////////
//
//layout(location = 0) in vec3 vp;
//layout(location = 1) in vec4 vertex_rgb;
//
//uniform mat4 modelMatrix;
//out vec4 color;
//
//void main() {
//	color = vertex_rgb;
//	gl_Position = modelMatrix * vec4(vp, 1.0);
//}


///////// 2 ////////////
in vec3 vp; 
uniform mat4 modelMatrix; 
out vec3 position; 

void main() {
    position = vp; 
    gl_Position = modelMatrix * vec4(vp, 1.0); 
}