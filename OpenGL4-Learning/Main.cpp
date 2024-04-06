#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>

#include "GLLog.h"

using namespace std;

void glfw_error_callback(int error, const char* description);
void GetWindowInput(GLFWwindow* window);

int main(void)
{

	assert(restart_gl_log());

	gl_log("starting GLFW\n%s\n", glfwGetVersionString());
	glfwSetErrorCallback(glfw_error_callback);

	/* Initialize the library */
	if (!glfwInit()) {
		fprintf(stderr, "Error: Could not start GLFW3 \n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 16);

	GLFWmonitor* mon = glfwGetPrimaryMonitor();
	const GLFWvidmode* vmode = glfwGetVideoMode(mon);

	GLFWwindow* window = glfwCreateWindow(vmode->width, vmode->height, "OpenGL_4", mon, NULL);
	if (!window)
	{
		fprintf(stderr, "Error: Could not open window with GLFW3 \n");
		glfwTerminate();
		return -2;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLfloat points[] = {
		 0.0f,  0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	const char* vertex_shader =
		"#version 400\n"
		"layout(location = 0) in vec3 vp;"
		"void main() {"
		"  gl_Position = vec4(vp, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main() {"
		"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
		"}";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);


	while (!glfwWindowShouldClose(window))
	{
		// wipe the drawing surface clear
		glClearColor(.5f, .5f, .5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		glBindVertexArray(vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
		GetWindowInput(window);
	}

	glfwTerminate();
	return 0;
}

void glfw_error_callback(int error, const char* description)
{
	gl_log_err("GLFW ERROR: code %i msg: %s\n", error, description);
}

void GetWindowInput(GLFWwindow* window)
{
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, 1);
	}
}
