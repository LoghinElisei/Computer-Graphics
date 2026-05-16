#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <cmath>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" 

#define M_PI 3.14159265358979323846

std::vector<float> sphereVertices;
std::vector<unsigned int> sphereIndices;

GLuint shader_programme, vao;
GLuint noiseTexture;

float noiseDelta = 0.005f;
float rotationAngle = 0.0f;
float lightX = 2.0f;
float lightY = 2.0f;
float lightZ = 2.0f;

std::string textFileRead(char* fn) {
    std::ifstream ifile(fn);
    std::string filetext;
    while (ifile.good()) {
        std::string line;
        std::getline(ifile, line);
        filetext.append(line + "\n");
    }
    return filetext;
}

void generateSphere(float radius, int sectorCount, int stackCount) {
    float x, y, z, xy;
    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i) {
        stackAngle = M_PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        y = radius * sinf(stackAngle);

        for (int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            z = xy * sinf(sectorAngle);

            sphereVertices.push_back(x);
            sphereVertices.push_back(y);
            sphereVertices.push_back(z);
        }
    }

    int k1, k2;
    for (int i = 0; i < stackCount; ++i) {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                sphereIndices.push_back(k1);
                sphereIndices.push_back(k2);
                sphereIndices.push_back(k1 + 1);
            }
            if (i != (stackCount - 1)) {
                sphereIndices.push_back(k1 + 1);
                sphereIndices.push_back(k2);
                sphereIndices.push_back(k2 + 1);
            }
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_programme);

    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform1f(glGetUniformLocation(shader_programme, "delta"), noiseDelta);

    glUniform3f(glGetUniformLocation(shader_programme, "lightPos"), lightX, lightY, lightZ);
    glUniform3f(glGetUniformLocation(shader_programme, "viewPos"), 0.0f, 0.0f, 3.0f);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, noiseTexture);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);

    glFlush();
}


void keyboard(unsigned char key, int x, int y) {
    if (key == 'e')
    {
        noiseDelta += 0.001f;
    }
    else if (key == 'q')
    {
        noiseDelta-= 0.001f;
    }
    else if (key == 'a')
    {
        rotationAngle += 5.0f;
    }
    else if (key == 'd')
    {
        rotationAngle -= 5.0f;
    }
    else if (key == '1')
    {
        lightX -= 0.2f;
    }
    else if (key == '2')
    {
        lightX += 0.2f;
    }
    else if (key == '3')
    {
        lightY -= 0.2f;
    }
    else if (key == '4')
    {
        lightY += 0.2f;
    }

    glutPostRedisplay();
}


void init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glewInit();

    generateSphere(0.7f, 36, 18);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(float), sphereVertices.data(), GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(unsigned int), sphereIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenTextures(1, &noiseTexture);
    glBindTexture(GL_TEXTURE_2D, noiseTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("noise.png", &width, &height, &nrChannels, 1); // 1 = force 1 channel

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load noise texture" << std::endl;
    }
    stbi_image_free(data);

    std::string vstext = textFileRead((char*)"vertex.vert");
    std::string fstext = textFileRead((char*)"fragment.frag");
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
    glUniform1i(glGetUniformLocation(shader_programme, "noiseTex"), 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(800, 800);
    glutCreateWindow("SPG - Sfera");

    init();

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}