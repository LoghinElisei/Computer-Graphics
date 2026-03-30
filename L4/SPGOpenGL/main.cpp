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
float points[] = {
	0.0f,  0.5f,  0.0f,
	0.5f, -0.5f,  0.0f,
	-0.5f, -0.5f,  0.0f
};

GLuint shader_programme, vao;
glm::mat4 model;

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

	float rotationAngle = glm::pi<float>() / 2;

	glm::mat4 rotationMatrix{  glm::cos(rotationAngle), glm::sin(rotationAngle), 0, 0,
							  -glm::sin(rotationAngle), glm::cos(rotationAngle), 0, 0,
								0,0,1,0, 
								0,0,0,1 
							};

	GLuint matrixID = glGetUniformLocation(shader_programme, "modelMatrix");
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(rotationMatrix));

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

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
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

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

float tx= -0.5f;
float ty= 0;
float tz = 0;
float T[] = { 1,0,0,0,
		0,1,0,0,
		0,0,0,1,
		tx,ty,tz,1 };

void display_p2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader_programme);


	GLuint matrixID = glGetUniformLocation(shader_programme, "modelMatrix");
	glm::mat4 transl = glm::translate(glm::vec3(-0.5f,0,0));
	glUniformMatrix4fv(matrixID,1, GL_FALSE, glm::value_ptr(transl));
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(vao);
	
	float rotationAngle = glm::pi<float>() / 2;
	glm::mat4 rotationMatrix{ glm::cos(rotationAngle), glm::sin(rotationAngle), 0, 0,
							  -glm::sin(rotationAngle), glm::cos(rotationAngle), 0, 0,
								0,0,1,0,
								0,0,0,1
	};

	GLuint matrixID2 = glGetUniformLocation(shader_programme, "modelMatrix");
	glUniformMatrix4fv(matrixID2, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glm::mat4 transl2 = glm::translate(glm::vec3(0.5f,0,0));
	glm::mat4 move = rotationMatrix * transl2;
	glUniformMatrix4fv(matrixID2, 1, GL_FALSE, glm::value_ptr(move));
	
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glFlush();
}

void display_p3()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader_programme);

	

	GLuint matrixID = glGetUniformLocation(shader_programme, "modelMatrix");
	glm::mat4 transl = glm::translate(glm::vec3(-0.5f, 0, 0));
	float rotationAngle = glm::pi<float>() / 2;
	glm::mat4 rotationMatrix{ glm::cos(rotationAngle), glm::sin(rotationAngle), 0, 0,
							  -glm::sin(rotationAngle), glm::cos(rotationAngle), 0, 0,
								0,0,1,0,
								0,0,0,1
	};
	glm::mat4 scale = glm::scale(glm::vec3(-0.5f, -0.5f, 0));

	glm::mat4 move = rotationMatrix *  transl *  scale;

	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(move));
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(vao);

	glFlush();
}

void display_p4()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader_programme);

	float rotationAngle = glm::pi<float>() / 2;

	glm::mat4 rotationMatrix{ glm::cos(rotationAngle), glm::sin(rotationAngle), 0, 0,
							  -glm::sin(rotationAngle), glm::cos(rotationAngle), 0, 0,
								0,0,1,0,
								0,0,0,1
	};

	GLuint matrixID = glGetUniformLocation(shader_programme, "modelMatrix");
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(rotationMatrix));

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glFlush();

	//vec3 newPosition = vec3(vp.x * 0.5f, vp.y * 0.5f - 0.5f, vp.z);
	//gl_Position = modelMatrix * vec4(newPosition, 1.0);
}

void display_p5()
{

}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(512, 512);
	glutCreateWindow("SPG");

	init();

	glutDisplayFunc(display_p3);
	glutMainLoop();

	return 0;
}
