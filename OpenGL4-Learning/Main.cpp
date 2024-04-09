#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>

#include "GLLog.h"
#include "Shader.h"

using namespace std;

int g_gl_width = 640;
int g_gl_height = 480;

void glfw_error_callback(int error, const char* description);
void glfw_window_size_callback(GLFWwindow* window, int with, int height);

void _update_fps_counter(GLFWwindow* window);
void GetWindowInput(GLFWwindow* window);
void GetWindowFullScreen();
bool CheckShaderLog(GLuint shader_index);
bool CheckShaderProgrammeLog(GLuint program_index);

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



	GLFWwindow* window = glfwCreateWindow(g_gl_width, g_gl_height, "OpenGL_4", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Error: Could not open window with GLFW3 \n");
		glfwTerminate();
		return -2;
	}
	glfwSetWindowSizeCallback(window, glfw_window_size_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	log_gl_params();

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	GLfloat points[] = {
		 0.0f,  0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
	};
	GLfloat colours[] = {
		 1.0f, 0.0f,  0.0f,
		 0.0f, 1.0f,  0.0f,
		 0.0f, 0.0f,  1.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint vbo_colours = 0;
	glGenBuffers(1, &vbo_colours);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_colours);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_colours);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	string vShader = ShaderUtility::GetShader("vertexShader.glsl");
	const char* vertex_shader = vShader.c_str();
	cout << "Vertext Shader: " << endl << vShader << endl;
	cout << "---------------" << endl << endl;
	string fShader = ShaderUtility::GetShader("fragmentShader.glsl");
	const char* fragment_shader = fShader.c_str();
	cout << "Fragment Shader: " << endl << fShader << endl;
	cout << "---------------" << endl << endl;
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	CheckShaderLog(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	CheckShaderLog(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, vs);
	glAttachShader(shader_programme, fs);

	glLinkProgram(shader_programme);
	CheckShaderProgrammeLog(shader_programme);
	print_all_programme_log(shader_programme);



	while (!glfwWindowShouldClose(window))
	{
		_update_fps_counter(window);
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

void glfw_window_size_callback(GLFWwindow* window, int with, int height)
{
	g_gl_width = with;
	g_gl_height = height;

	glViewport(0, 0, g_gl_width, g_gl_height);
}

void _update_fps_counter(GLFWwindow* window)
{
	static double previous_seconds = glfwGetTime();
	static int frame_count;
	double current_seconds = glfwGetTime();
	double elapsed_seconds = current_seconds - previous_seconds;

	if (elapsed_seconds > 0.25)
	{
		previous_seconds = current_seconds;
		double fps = (double)frame_count / elapsed_seconds;
		char tmp[128];
		sprintf_s(tmp, "opengl @ fps: %.2f", fps);
		glfwSetWindowTitle(window, tmp);
		frame_count = 0;
	}

	frame_count++;
}

void GetWindowInput(GLFWwindow* window)
{
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, 1);
	}
}

void GetWindowFullScreen()
{
	GLFWmonitor* mon = glfwGetPrimaryMonitor();
	const GLFWvidmode* vmode = glfwGetVideoMode(mon);
	g_gl_width = vmode->width;
	g_gl_height = vmode->height;
}

bool CheckShaderLog(GLuint shader_index)
{
	int params = -1;
	glGetShaderiv(shader_index, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params)
	{
		printf("ERROR: GL shader index %i did not compile\n", shader_index);
		_print_shader_info_log(shader_index);
		return false;
	}

	return true;
}

bool CheckShaderProgrammeLog(GLuint program_index)
{
	int params = -1;
	glGetProgramiv(program_index, GL_LINK_STATUS, &params);
	if (GL_TRUE != params)
	{
		printf("ERROR: could not link shader programme GL index %u\n", program_index);
		_print_programme_info_log(program_index);
		return false;
	}
	return true;
}
