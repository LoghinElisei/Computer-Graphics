#version 400
out vec4 fragColor;

in vec3 normal;
in vec3 pos;

uniform vec3 lightPos;
uniform vec3 viewPos;

vec3 lighting(vec3 pos, vec3 normal, vec3 lightPos, vec3 viewPos,
				vec3 ambient, vec3 diffuse, vec3 specular, float specPower)
{
	vec3 N = normalize(normal);
	vec3 L = normalize(lightPos - pos);
	vec3 V = normalize(viewPos - pos);
	vec3 R = reflect(-L, N);
	
	vec3 compAmbient = ambient;
	
	float diff = max(dot(N, L), 0.0);
	vec3 compDiffuse = diffuse * diff;
	
	float spec = 0.0;
	if(diff > 0.0) { 
		spec = pow(max(dot(R, V), 0.0), specPower);
	}
	vec3 compSpecular = specular * spec;
	
	return compAmbient + compDiffuse + compSpecular;

	return vec3(0);
}

void main() 
{
	vec3 ambient = vec3(0.2);
	vec3 diffuse = vec3(1.0, 0, 0);
	vec3 specular = vec3(0.8);
	float specPower = 32;
	
	vec3 color = lighting(pos, normal, lightPos, viewPos, 
				ambient, diffuse, specular, specPower);
				
	fragColor = vec4(color, 1.0);
}
