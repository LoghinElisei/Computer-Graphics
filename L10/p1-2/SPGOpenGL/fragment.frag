#version 400
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D ourTexture;
void main()
{
	 //1
	 //FragColor = texture(ourTexture, TexCoord);
	 //2
	 FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
}