#version 400
out vec4 frag_colour;

uniform vec3 myColor;
void main() {

frag_colour = vec4(myColor, 1.0);
}