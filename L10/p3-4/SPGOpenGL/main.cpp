//#include <iostream>
//#include <fstream>
//#include <string>
//
//#include <stdio.h>
//
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//
//#include <glm/mat4x4.hpp>
//#include <glm/gtx/transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h" 
//
//float vertices[] = {
//    // positions          // colors           // texture coords
//     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, 
//     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, 
//    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 
//    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  
//};
//
//unsigned int indices[] = {
//    0, 1, 3, // primul triunghi
//    1, 2, 3  // al doilea triunghi
//};
//
//GLuint shader_programme, vao;
//GLuint texture;
//
//std::string textFileRead(char* fn)
//{
//    std::ifstream ifile(fn);
//    std::string filetext;
//    while (ifile.good()) {
//        std::string line;
//        std::getline(ifile, line);
//        filetext.append(line + "\n");
//    }
//    return filetext;
//}
//
//void display()
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//    glUseProgram(shader_programme);
//
//    glm::mat4 model = glm::mat4(1.0f);
//
//    GLuint matrixID = glGetUniformLocation(shader_programme, "modelMatrix");
//    glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(model));
//
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, texture);
//
//    glBindVertexArray(vao);
//
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//    glFlush();
//}
//
//void init()
//{
//    const GLubyte* renderer = glGetString(GL_RENDERER);
//    const GLubyte* version = glGetString(GL_VERSION);
//    printf("Renderer: %s\n", renderer);
//    printf("OpenGL version supported %s\n", version);
//
//    glClearColor(1, 1, 1, 0);
//
//    glewInit();
//
//    vao = 0;
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//
//    GLuint vbo = 1;
//    glGenBuffers(1, &vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    GLuint ebo;
//    glGenBuffers(1, &ebo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    // Pozitia
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // Culoarea
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    // texturare
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//
//    //v1
//    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
//    //v2
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//    int width, height, nrChannels;
//    stbi_set_flip_vertically_on_load(true);
//    unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
//
//    if (data) {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//
//    std::string vstext = textFileRead("vertex.vert");
//    std::string fstext = textFileRead("fragment.frag");
//    const char* vertex_shader = vstext.c_str();
//    const char* fragment_shader = fstext.c_str();
//
//    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vs, 1, &vertex_shader, NULL);
//    glCompileShader(vs);
//
//    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fs, 1, &fragment_shader, NULL);
//    glCompileShader(fs);
//
//    shader_programme = glCreateProgram();
//    glAttachShader(shader_programme, fs);
//    glAttachShader(shader_programme, vs);
//    glLinkProgram(shader_programme);
//}
//
//int main(int argc, char** argv)
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//    glutInitWindowPosition(200, 200);
//    glutInitWindowSize(512, 512);
//    glutCreateWindow("SPG");
//
//    init();
//
//    glutDisplayFunc(display);
//    glutMainLoop();
//
//    return 0;
//}



#include <iostream>
#include <fstream>
#include <string>

#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" 

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f
};

unsigned int indices[] = {
    0, 1, 3, // primul triunghi
    1, 2, 3  // al doilea triunghi
};

GLuint shader_programme, vao;
GLuint texture1,texture2;

std::string textFileRead(char* fn)
{
    std::ifstream ifile(fn);
    std::string filetext;
    while (ifile.good()) {
        std::string line;
        std::getline(ifile, line);
        filetext.append(line + "\n");
    }
    return filetext;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader_programme);

    glm::mat4 model = glm::mat4(1.0f);

    GLuint matrixID = glGetUniformLocation(shader_programme, "modelMatrix");
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(model));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glFlush();
}

void init()
{
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    glClearColor(1, 1, 1, 0);

    glewInit();

    vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo = 1;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Pozitia
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Culoarea
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texturare
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    //v1
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //v2
    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned char* data2 = stbi_load("wood.jpg", &width, &height, &nrChannels, 0);

    if (data2) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture 2" << std::endl;
    }

    std::string vstext = textFileRead("vertex.vert");
    std::string fstext = textFileRead("fragment.frag");
    const char* vertex_shader = vstext.c_str();
    const char* fragment_shader = fstext.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);

    glUseProgram(shader_programme); 
    glUniform1i(glGetUniformLocation(shader_programme, "texture1"), 0); 
    glUniform1i(glGetUniformLocation(shader_programme, "texture2"), 1); 
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(512, 512);
    glutCreateWindow("SPG");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}