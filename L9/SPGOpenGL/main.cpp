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
#include <vector>
#include <stack>

#include "objloader.hpp"

#define PI glm::pi<float>()

GLuint shader_programme;
glm::mat4 projectionMatrix, viewMatrix, modelMatrix;
std::stack<glm::mat4> modelStack;

std::vector< glm::vec3 > verticesNormals;

GLuint vaoObj, vboObj;

std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals;

float xv = 10, yv = 12, zv = 30; //originea sistemului de observare

glm::vec3 lightPos(0, 20000, 0);
glm::vec3 viewPos(2, 3, 6);

float axisRotAngle = PI / 16.0; // unghiul de rotatie in jurul propriei axe
float radius = 2;
float scaleFactor = 0.01;

void printShaderInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		free(infoLog);
	}
}

void printProgramInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		free(infoLog);
	}
}

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

void init()
{
	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);


	bool res = loadOBJ("obj/scrat.obj", vertices, uvs, normals);

	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 0);

	glewInit();

	verticesNormals = vertices;
	verticesNormals.insert(verticesNormals.end(), normals.begin(), normals.end());

	glGenBuffers(1, &vboObj);
	glBindBuffer(GL_ARRAY_BUFFER, vboObj);
	glBufferData(GL_ARRAY_BUFFER, verticesNormals.size() * sizeof(glm::vec3), &verticesNormals[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &vaoObj);
	glBindVertexArray(vaoObj);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(vertices.size() * sizeof(glm::vec3)));

	std::string vstext = textFileRead("vertex.vert");
	std::string fstext = textFileRead("fragment.frag");
	const char* vertex_shader = vstext.c_str();
	const char* fragment_shader = fstext.c_str();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	// check for shader compile errors
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fs, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	printShaderInfoLog(fs);
	printShaderInfoLog(vs);
	printProgramInfoLog(shader_programme);
}

void display()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glUseProgram(shader_programme);

	//glBindVertexArray(vaoObj);

	//GLuint lightPosLoc = glGetUniformLocation(shader_programme, "lightPos");
	//glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));

	//GLuint viewPosLoc = glGetUniformLocation(shader_programme, "viewPos");
	//glUniform3fv(viewPosLoc, 1, glm::value_ptr(viewPos));

	//modelMatrix = glm::mat4(); // matricea de modelare este matricea identitate
	//modelMatrix *= glm::rotate(axisRotAngle, glm::vec3(0, 1, 0));
	//modelMatrix *= glm::scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
	//GLuint modelMatrixLoc = glGetUniformLocation(shader_programme, "modelViewProjectionMatrix");
	//glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix * viewMatrix * modelMatrix));

	//glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelMatrix));
	//GLuint normalMatrixLoc = glGetUniformLocation(shader_programme, "normalMatrix");
	//glUniformMatrix4fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	//glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	//glutSwapBuffers();


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader_programme);

	glBindVertexArray(vaoObj);

	glm::vec3 currentViewPos(xv, yv, zv);
	glm::vec3 lightPos2 = currentViewPos; 

	glUniform3fv(glGetUniformLocation(shader_programme, "lightPos"), 1, glm::value_ptr(lightPos));
	glUniform3fv(glGetUniformLocation(shader_programme, "lightPos2"), 1, glm::value_ptr(lightPos2));
	glUniform3fv(glGetUniformLocation(shader_programme, "viewPos"), 1, glm::value_ptr(currentViewPos));

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::rotate(modelMatrix, axisRotAngle, glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleFactor));

	glUniformMatrix4fv(glGetUniformLocation(shader_programme, "modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix * viewMatrix * modelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader_programme, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader_programme, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(15.0f, 0.0f, 5.0f));
	modelMatrix = glm::rotate(modelMatrix, axisRotAngle * 1.5f, glm::vec3(1, 0, 0)); 
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleFactor * 0.5f)); 

	glUniformMatrix4fv(glGetUniformLocation(shader_programme, "modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix * viewMatrix * modelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader_programme, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

	normalMatrix = glm::transpose(glm::inverse(modelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader_programme, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	projectionMatrix = glm::perspective(PI / 4, (float)w / h, 0.1f, 1000.0f);
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
	case '+':
		scaleFactor += 0.01;
		break;
	case '-':
		scaleFactor -= 0.01;
	};
	glutPostRedisplay(); // cauzeaza redesenarea ferestrei
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		zv -= 0.5f;
		break;
	case GLUT_KEY_DOWN:
		zv += 0.5f;
		break;
	case GLUT_KEY_LEFT:
		xv -= 0.5f;
		break;
	case GLUT_KEY_RIGHT:
		xv += 0.5f;
		break;
	}
	viewMatrix = glm::lookAt(glm::vec3(xv, yv, zv), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glutPostRedisplay();
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
	glutSpecialFunc(specialKeys);
	glutMainLoop();

	return 0;
}
