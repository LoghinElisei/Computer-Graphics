#include <iostream>
#include <fstream>
#include <string>

#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//varfurile triunghiului
//float points[] = {
//	0.0f,  0.5f,  0.0f,
//	0.5f, -0.5f,  0.0f,
//	-0.5f, -0.5f,  0.0f
//};
float points[] = {
	-0.5f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f, 1.0f,  //r
	-0.5f, -0.5f,  0.0f,   0.0f, 1.0f, 0.0f, 1.0f,  //g
	 0.5f, -0.5f,  0.0f,   0.0f, 0.0f, 1.0f, 1.0f,  //b

	 -0.5f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f, 1.0f, 
	  0.5f, -0.5f,  0.0f,   0.0f, 0.0f, 1.0f, 1.0f, 
	  0.5f,  0.5f,  0.0f,   1.0f, 1.0f, 0.0f, 1.0f 
};

GLuint shader_programme, vao;

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



void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader_programme);

	glm::mat4 model = glm::mat4(1.0f); 
		
	//model *= glm::rotate(glm::radians(90.0f), glm::vec3(0, 0, 1));
	 

	GLuint matrixID = glGetUniformLocation(shader_programme, "modelMatrix");
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);

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
	glBufferData(GL_ARRAY_BUFFER, 42 * sizeof(float), points, GL_STATIC_DRAW);

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	//pozitia
	glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);

	//culoarea
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

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
