#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
//varfurile triunghiului
//float points[] = {
//0.0f, 0.5f, 0.0f,
//0.5f, -0.5f, 0.0f,
//-0.5f, -0.5f, 0.0f
//};

//varfurile patratului
float points[] = {
	-0.5f, 0.5f, 0.0f,    //vf 1
	-0.5f, -0.5f, 0.0f, //vf 3
	0.5f, -0.5f, 0.0f, //vf4
	-0.5f, 0.5f, 0.0f,   //vf 1
	0.5f, -0.5f, 0.0f, //vf4
	0.5f, 0.5f, 0.0f	//vf 2
	
};


GLuint shader_programme, vao;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader_programme);
	glBindVertexArray(vao);
	//glDrawArrays(GL_TRIANGLES, 0, 3);   // 3 - nr of peaks, 0 - indexed

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	glutSwapBuffers();
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
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);
	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	const char* vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"void main() {"
		" gl_Position = vec4(vp, 1.0);"
		"}";
	const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main() {"
		" frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
		"}";
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
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(512, 512);
	glutCreateWindow("SPG");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}


////////////////////////////////////////////////////
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <stdio.h>
//#include <cmath>
////varfurile triunghiului
////float points[] = {
////0.0f, 0.5f, 0.0f,
////0.5f, -0.5f, 0.0f,
////-0.5f, -0.5f, 0.0f
////};
//
////varfurile patratului
////float points[] = {
////	0.0f, 0.0f, 0.0f,    //vf 1
////	0.5f, 0.0f, 0.0f, //vf 2
////	0.5f, 0.5f, 0.0f, //vf3
////};
//
//const int n = 16; // n triunghiuri
//float r = 0.5f;
//float PI = 3.14;
//float points[9 * n];
//
//GLuint shader_programme, vao;
//
//
//void init_points()
//{
//	for (int i = 0; i < n; i++)
//	{
//		float u1 = 2 * PI * i / n;
//		float u2 = 2 * PI * (i + 1) / n;
//
//		//centru
//		points[i * 9] = points[i * 9 + 1] = points[i * 9 + 2] = 0.0f;
//
//		//vf i
//		points[9 * i + 3] = r * cos(u1); //x
//		points[9 * i + 4] = r * sin(u1); //y
//		points[9 * i + 5] = 0.0f; //z
//
//		//vf i+1
//		points[9 * i + 6] = r * cos(u2); //x
//		points[9 * i + 7] = r * sin(u2); //y
//		points[9 * i + 8] = 0.0f;
//	}
//}
//
//void display()
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//	glUseProgram(shader_programme);
//	glBindVertexArray(vao);
//	//glDrawArrays(GL_TRIANGLES, 0, 3);   // 3 - nr of peaks, 0 - indexed
//
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glDrawArrays(GL_TRIANGLES, 0, 3*n);
//
//	glutSwapBuffers();
//}
//
//
//
//
//
//
//void init()
//{
//	// get version info
//	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
//	const GLubyte* version = glGetString(GL_VERSION); // version as a string
//	printf("Renderer: %s\n", renderer);
//	printf("OpenGL version supported %s\n", version);
//	glClearColor(1, 1, 1, 0);
//
//	glewInit();
//	GLuint vbo = 1;
//	glGenBuffers(1, &vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, 9*n * sizeof(float), points, GL_STATIC_DRAW);
//	vao = 0;
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//	const char* vertex_shader =
//		"#version 400\n"
//		"in vec3 vp;"
//		"void main() {"
//		" gl_Position = vec4(vp, 1.0);"
//		"}";
//	const char* fragment_shader =
//		"#version 400\n"
//		"out vec4 frag_colour;"
//		"void main() {"
//		" frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
//		"}";
//	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vs, 1, &vertex_shader, NULL);
//	glCompileShader(vs);
//	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fs, 1, &fragment_shader, NULL);
//	glCompileShader(fs);
//	shader_programme = glCreateProgram();
//	glAttachShader(shader_programme, fs);
//	glAttachShader(shader_programme, vs);
//	glLinkProgram(shader_programme);
//}
//int main(int argc, char** argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGB);
//	glutInitWindowPosition(200, 200);
//	glutInitWindowSize(512, 512);
//	glutCreateWindow("SPG");
//	init_points();
//	init();
//	glutDisplayFunc(display);
//	glutMainLoop();
//	return 0;
//}

//////////////////////////////////////////////////
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <stdio.h>
//#include <cmath>
////varfurile triunghiului
////float points[] = {
////0.0f, 0.5f, 0.0f,
////0.5f, -0.5f, 0.0f,
////-0.5f, -0.5f, 0.0f
////};
//
////varfurile patratului
////float points[] = {
////	0.0f, 0.0f, 0.0f,    //vf 1
////	0.5f, 0.0f, 0.0f, //vf 2
////	0.5f, 0.5f, 0.0f, //vf3
////};
//
//const int n = 16; // n triunghiuri
//float r = 0.5f;
//float PI = 3.14;
//float points[3 * (n+1)];
//unsigned int indices[3 * n];
//GLuint shader_programme, vao;
//
//void init_points()
//{
//	points[0] = points[1] = points[2] = 0.0f; //centru
//	//vf
//	for (int i = 1; i <= n; i++)
//	{
//		float u = 2 * PI * i / n;
//		points[3 * i] = r * cos(u);
//		points[3 * i + 1] = r * sin(u);
//		points[3 * i + 2] = 0.0f;
//	}
//
//	//indici 0, i+1, i+2
//	for (int i = 0; i < n - 1; i++)
//	{
//		indices[3 * i] = 0;
//		indices[3 * i + 1] = i + 1;
//		indices[3 * i + 2] = i + 2;
//	}
//
//	indices[3 * (n - 1)] = 0;
//	indices[3 * (n - 1) + 1] = n;
//	indices[3 * (n - 1) + 2] = 1;
//}
//
//void display()
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//	glUseProgram(shader_programme);
//	glBindVertexArray(vao);
//	//glDrawArrays(GL_TRIANGLES, 0, 3);   // 3 - nr of peaks, 0 - indexed
//
//	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glDrawArrays(GL_TRIANGLES, 0, 3 * n);*/
//
//	glDrawElements(GL_TRIANGLES, 3 * (n + 1), GL_UNSIGNED_INT, 0);
//
//	glutSwapBuffers();
//}
//
//void init()
//{
//	// get version info
//	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
//	const GLubyte* version = glGetString(GL_VERSION); // version as a string
//	printf("Renderer: %s\n", renderer);
//	printf("OpenGL version supported %s\n", version);
//	glClearColor(1, 1, 1, 0);
//
//	glewInit();
//	GLuint vbo = 1;
//	glGenBuffers(1, &vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER,sizeof(points), points, GL_STATIC_DRAW);
//	vao = 0;
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//
//
//	GLuint ebo;
//	glGenBuffers(1, &ebo);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//	const char* vertex_shader =
//		"#version 400\n"
//		"in vec3 vp;"
//		"void main() {"
//		" gl_Position = vec4(vp, 1.0);"
//		"}";
//	const char* fragment_shader =
//		"#version 400\n"
//		"out vec4 frag_colour;"
//		"void main() {"
//		" frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
//		"}";
//	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vs, 1, &vertex_shader, NULL);
//	glCompileShader(vs);
//	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fs, 1, &fragment_shader, NULL);
//	glCompileShader(fs);
//	shader_programme = glCreateProgram();
//	glAttachShader(shader_programme, fs);
//	glAttachShader(shader_programme, vs);
//	glLinkProgram(shader_programme);
//}
//
//int main(int argc, char** argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGB);
//	glutInitWindowPosition(200, 200);
//	glutInitWindowSize(512, 512);
//	glutCreateWindow("SPG");
//	init_points();
//	init();
//	glutDisplayFunc(display);
//	glutMainLoop();
//	return 0;
//}