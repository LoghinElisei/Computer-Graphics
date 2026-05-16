#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint shader_programme, vao;
glm::mat4 projection, view, model, mvp;
unsigned int texture1, texture2;

std::string textFileRead(const char* fn) {
    std::ifstream ifile(fn);
    std::string filetext;
    while (ifile.good()) {
        std::string line;
        std::getline(ifile, line);
        filetext.append(line + "\n");
    }
    return filetext;
}

float vertices[] = {
    -0.5f,  0.5f,  0.0f,    1.0f, 1.0f, 1.0f, 1.0f,      0.0f, 1.0f, // Stânga Sus
     0.5f,  0.5f,  0.0f,    1.0f, 1.0f, 1.0f, 1.0f,      1.0f, 1.0f, // Dreapta Sus
     0.0f, -0.5f,  0.0f,    1.0f, 1.0f, 1.0f, 1.0f,      0.5f, 0.0f, // Mijloc Jos

     -0.5f, -0.2f,  0.5f,    1.0f, 1.0f, 1.0f, 0.6f,      0.0f, 0.0f, // Stânga Jos
      0.5f, -0.2f,  0.5f,    1.0f, 1.0f, 1.0f, 0.6f,      1.0f, 0.0f, // Dreapta Jos
      0.0f,  0.8f,  0.5f,    1.0f, 1.0f, 1.0f, 0.6f,      0.5f, 1.0f  // Mijloc Sus
};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_programme);

    model = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(0, 0, 1));
    mvp = projection * view * model;

    GLuint matrixID = glGetUniformLocation(shader_programme, "MVP");
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(glGetUniformLocation(shader_programme, "texture1"), 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(glGetUniformLocation(shader_programme, "texture2"), 1);

    glBindVertexArray(vao);

    glUniform1i(glGetUniformLocation(shader_programme, "texIndex"), 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUniform1i(glGetUniformLocation(shader_programme, "texIndex"), 1);
    glDrawArrays(GL_TRIANGLES, 3, 3);

    glutSwapBuffers();
}

void init()
{
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    projection = glm::ortho(-1.2f, 1.2f, -1.2f, 1.2f, 0.1f, 100.0f);

    view = glm::lookAt(
        glm::vec3(0, 0, 3),  
        glm::vec3(0, 0, 0),  
        glm::vec3(0, 1, 0)  
    );
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(700, 700);
    glutCreateWindow("SPG L11");

    glewInit();
    init();

    stbi_set_flip_vertically_on_load(true);

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    int width, height, nrChannels;
    unsigned char* data1 = stbi_load("wallg.jpg", &width, &height, &nrChannels, 0);
    if (data1) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Nu s-a putut incarca wallg.jpg!" << std::endl;
    }
    stbi_image_free(data1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    unsigned char* data2 = stbi_load("wood.jpg", &width, &height, &nrChannels, 0);
    if (data2) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Nu s-a putut incarca wood.jpg!" << std::endl;
    }
    stbi_image_free(data2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);

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

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}