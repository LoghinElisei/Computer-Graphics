#version 400

///////// 3 ////////
//layout(location = 0) in vec3 vp;
//uniform mat4 modelViewProjectionMatrix;
//
//out vec3 FragPos;
//
//void main()
//{
//	FragPos = vp;
//	gl_Position = modelViewProjectionMatrix * vec4(vp, 1.0);
//}

//////// 4 /////////


layout(location = 0) in vec3 vp; 
uniform mat4 modelViewProjectionMatrix; 

out vec3 FragPos; 

void main() 
{
    FragPos = vp; 
    gl_Position = modelViewProjectionMatrix * vec4(vp, 1.0); 
}