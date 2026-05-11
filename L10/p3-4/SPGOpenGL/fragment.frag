#version 400
//ex 3
//out vec4 FragColor;
//
//in vec3 ourColor;
//in vec2 TexCoord;
//uniform sampler2D ourTexture;
//void main()
//{
//    //1
//    //FragColor = texture(ourTexture, TexCoord);
//    //2
//    FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
//}


//ex 4
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
}