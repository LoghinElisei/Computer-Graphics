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

#define PI glm::pi<float>()

GLuint shader_programme, vao;
glm::mat4 projectionMatrix, viewMatrix;
float points[] = {
	// === CUB (muchii) ===
	// Fața din spate (z = -0.5)
	-0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,

	// Fața din față (z = 0.5)
	-0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f,

	// Liniile de legătură între fețe
	-0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f,

	// === AXE DE COORDONATE ===
	// Axa X (Roșu de obicei) - Lungime 16
	0.0f, 0.0f, 0.0f,
	16.0f, 0.0f, 0.0f,

	// Axa Y (Verde de obicei) - Lungime 8
	0.0f, 0.0f, 0.0f,
	0.0f, 8.0f, 0.0f,

	// Axa Z (Albastru de obicei) - Lungime 24
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 24.0f
};

float xv = 2, yv = 2, zv = 30; //originea sistemului de observare
float angle = 0.0f;


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
	float rotationAngle = PI / 2;
	glm::mat4 modelMatrix;
	glBindVertexArray(vao);
	GLuint matrixID = glGetUniformLocation(shader_programme,
		"modelViewProjectionMatrix");
	GLuint colorID = glGetUniformLocation(shader_programme,
		"myColor");

	//desenare axe coordonate
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix *
		viewMatrix * modelMatrix));
	glDrawArrays(GL_LINES, 24, 6);

	//desenare cub in centrul sistemului de coordonate
	glUniform3f(colorID, 1, 0, 0);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix *
		viewMatrix * modelMatrix));
	glDrawArrays(GL_LINES, 0, 24);

	//desenare cub 2
	glUniform3f(colorID, 0, 0, 1);
	modelMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, -8.0f, 0.0f)) * glm::scale(glm::mat4(1.0f),glm::vec3(2.0f, 2.0f, 2.0f));
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix * viewMatrix * modelMatrix));
	glDrawArrays(GL_LINES, 0, 24);
	
	//desenare cub 3
	glUniform3f(colorID, 0, 1, 0);
	rotationAngle = glm::pi<float>() / 4;

	glm::mat4 rotationMatrix{ glm::cos(rotationAngle), glm::sin(rotationAngle), 0, 0,
							  -glm::sin(rotationAngle), glm::cos(rotationAngle), 0, 0,
								0,0,1,0,
								0,0,0,1
	};

	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(8.0f,0.0f,0.0f)) *
		glm::rotate(glm::mat4(1.0f),glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * 
		glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 2.0f));

	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix * viewMatrix * modelMatrix));
	glDrawArrays(GL_LINES, 0, 24);

	//desenare cub 4
	glUniform3f(colorID, 1, 0, 1);
	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-8.0f, 0.0f, 0.0f)) *
					glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
					glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 2.0f));

	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix * viewMatrix * modelMatrix));
	glDrawArrays(GL_LINES, 0, 24);

	//desenare cub problema 3
	modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)) * modelMatrix;
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix * viewMatrix * modelMatrix));
	glDrawArrays(GL_LINES, 0, 24);
	glFlush();
}


void init()
{
	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
	glClearColor(1, 1, 1, 0);
	glewInit();
	GLuint vbo = 1;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
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
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	projectionMatrix = glm::perspective(PI / 3, (float)w / h, 0.1f, 100.0f);
	/*
	viewMatrix este matricea transformarii de observare. Parametrii functiei
	lookAt sunt trei vectori ce reprezinta, in ordine:
- pozitia observatorului
- punctul catre care priveste observatorul
- directia dupa care este orientat observatorul
*/
	viewMatrix = glm::lookAt(glm::vec3(xv, yv, zv), glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0));
}



void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
		angle -= 5.0f;
			break;
	case 'd':
		angle += 5.0f;
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
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