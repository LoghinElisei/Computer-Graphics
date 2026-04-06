#version 400
///////// 1 ////////////
//in vec4 color;
//out vec4 frag_colour;

//void main() {
//    frag_colour = color; 
//}


////////// 2 ////////////
out vec4 frag_colour; // 
in vec3 position; 

void main() {
  
    if (position.x < 0.0) {
        frag_colour = vec4(1.0, 1.0, 0.0, 1.0); 
    } 
    else {
        frag_colour = vec4(0.0, 0.0, 1.0, 1.0); 
    }
}