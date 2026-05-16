#version 400
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform int texIndex;

void main()
{
    vec4 texColor;
    
    if (texIndex == 0) {
        texColor = texture(texture1, TexCoord);
    } else {
        texColor = texture(texture2, TexCoord);
    }
    
    FragColor = texColor * ourColor;
}