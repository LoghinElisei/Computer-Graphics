#version 400
/////// 3 ///////
//in vec3 FragPos;
//out vec4 fragColor;
//
//void main()
//{
//
//	if (FragPos.x > 0.0)
//	{
//		fragColor = vec4(0.0, 1.0, 0.0, 1.0);
//	}
//	else
//	{
//		fragColor = vec4(0.0, 0.0, 1.0, 1.0);
//	}
//}

/////// 4 /////


in vec3 FragPos; 
out vec4 fragColor; 

void main() 
{
  
    vec3 normal = normalize(FragPos);
   
    vec3 axisX = vec3(1.0, 0.0, 0.0);

    float cosTheta = dot(normal, axisX);

    float intensity = clamp(cosTheta, 0.0, 1.0); 

    fragColor = vec4(0.0, 0.0, intensity, 1.0); 
}