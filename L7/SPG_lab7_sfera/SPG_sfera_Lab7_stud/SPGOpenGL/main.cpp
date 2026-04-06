#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include "spheremesh.h"
#include <stack>

#define PI glm::pi<float>()

GLuint shader_programme;
glm::mat4 projectionMatrix, viewMatrix, modelMatrix;
std::stack<glm::mat4> modelStack;

GLuint vboAxes, vaoAxes;
GLuint vboSphere, vaoSphere;
GLuint eboSphere; //index buffer pentru sfera

float axes[] = {
	//axele de coordonate
	0.0f, 0.0f, 0.0f,
	16.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 8.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 16.0f
};

SphereMesh sphere;
int sphereElementCount = (GLsizei)sphere.triangles.size() * sizeof(glm::ivec3);

float xv = 10, yv = 12, zv = 30; //originea sistemului de observare

std::string textFileRead(char *fn)
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


//
//
void init()
{
	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 0);

	glewInit();

	glGenBuffers(1, &vboAxes);
	glBindBuffer(GL_ARRAY_BUFFER, vboAxes);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), axes, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vaoAxes);
	glBindVertexArray(vaoAxes);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glGenBuffers(1, &vboSphere);
	glBindBuffer(GL_ARRAY_BUFFER, vboSphere);
	glBufferData(GL_ARRAY_BUFFER, sphere.vertices.size() * sizeof(glm::vec3), sphere.vertices.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &vaoSphere);
	glBindVertexArray(vaoSphere);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glGenBuffers(1, &eboSphere);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboSphere);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereElementCount, sphere.triangles.data(), GL_STATIC_DRAW);

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
}

float axisRotAngle = PI / 16.0; // unghiul de rotatie in jurul propriei axe
float radius = 2;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader_programme);

	GLuint matrixID = glGetUniformLocation(shader_programme, "modelViewProjectionMatrix");
	//GLuint colorID = glGetUniformLocation(shader_programme, "color");

	//desenare axe coordonate
	glBindVertexArray(vaoAxes);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix * viewMatrix * modelMatrix));
	//glUniform3fv(colorID, 1, glm::value_ptr(glm::vec3(0, 0, 0)));
	glDrawArrays(GL_LINES, 0, 6);

	// desenare sfera
	glBindVertexArray(vaoSphere);

	modelMatrix = glm::mat4(); // matricea de modelare este matricea identitate
	modelMatrix *= glm::rotate(axisRotAngle, glm::vec3(0, 1, 0)); 
	modelMatrix *= glm::scale(glm::vec3(2 * radius));

	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix * viewMatrix * modelMatrix));
	//glUniform3fv(colorID, 1, glm::value_ptr(glm::vec3(1, 0, 0)));
	glDrawElements(GL_TRIANGLES, sphereElementCount, GL_UNSIGNED_INT, NULL);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	projectionMatrix = glm::perspective(PI / 4, (float)w / h, 0.1f, 100.0f);
	/*
	viewMatrix este matricea transformarii de observare. Parametrii functiei
	lookAt sunt trei vectori ce reprezinta, in ordine:
	- pozitia observatorului
	- punctul catre care priveste observatorul
	- directia dupa care este orientat observatorul
	*/
	viewMatrix = glm::lookAt(glm::vec3(xv, yv, zv), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		axisRotAngle += 0.1;
		if (axisRotAngle > 2 * PI) 
			axisRotAngle = 0;

		break;
	case 's':

		axisRotAngle -= 0.1;
		if (axisRotAngle < 0) 
			axisRotAngle = 2 * PI;

		break;
	};
	glutPostRedisplay(); // cauzeaza redesenarea ferestrei
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(700, 700);
	glutCreateWindow("SPG");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
