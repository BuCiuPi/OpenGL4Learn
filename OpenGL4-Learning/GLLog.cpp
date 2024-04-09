
#include <iostream>
#include <time.h>
#include <stdarg.h>
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include "GLLog.h"

bool restart_gl_log()
{
	FILE* file;
	fopen_s(&file, GL_LOG_FILE, "w");

	if (!file)
	{
		fprintf(stderr, "ERROR: could not open GL_LOG_FILE log file %s for writing\n", GL_LOG_FILE);
		return false;
	}

	time_t now = time(NULL);
	char date[26];
	ctime_s(date, sizeof(date), &now);
	fprintf(file, "GL_LOG_FILE log. local time  %s\n", date);
	fclose(file);
	return true;
}

bool gl_log(const char* message, ...)
{
	va_list argptr;
	FILE* file;
	fopen_s(&file, GL_LOG_FILE, "a");
	if (!file) {
		fprintf(stderr, "ERROR: could not open GL_LOG_FILE log file %s for appending\n", GL_LOG_FILE);
		return false;
	}

	va_start(argptr, message);
	vfprintf(file, message, argptr);
	va_end(argptr);

	fclose(file);

	return true;
}

bool gl_log_err(const char* message, ...) {
	va_list argptr;
	FILE* file;
	fopen_s(&file, GL_LOG_FILE, "a");
	if (!file) {
		fprintf(stderr, "ERROR: could not open GL_LOG_FILE %s file for appending\n", GL_LOG_FILE);
		return false;
	}
	va_start(argptr, message);
	vfprintf(file, message, argptr);
	va_end(argptr);
	va_start(argptr, message);
	vfprintf(stderr, message, argptr);
	va_end(argptr);
	fclose(file);
	return true;
}

void log_gl_params() {
	GLenum params[] = {
		GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
		GL_MAX_CUBE_MAP_TEXTURE_SIZE,
		GL_MAX_DRAW_BUFFERS,
		GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
		GL_MAX_TEXTURE_IMAGE_UNITS,
		GL_MAX_TEXTURE_SIZE,
		GL_MAX_VARYING_FLOATS,
		GL_MAX_VERTEX_ATTRIBS,
		GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
		GL_MAX_VERTEX_UNIFORM_COMPONENTS,
		GL_MAX_VIEWPORT_DIMS,
		GL_STEREO,
	};
	const char* names[] = {
		"GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
		"GL_MAX_CUBE_MAP_TEXTURE_SIZE",
		"GL_MAX_DRAW_BUFFERS",
		"GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
		"GL_MAX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_TEXTURE_SIZE",
		"GL_MAX_VARYING_FLOATS",
		"GL_MAX_VERTEX_ATTRIBS",
		"GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_VERTEX_UNIFORM_COMPONENTS",
		"GL_MAX_VIEWPORT_DIMS",
		"GL_STEREO",
	};
	gl_log("GL Context Params:\n");
	char msg[256];
	// integers - only works if the order is 0-10 integer return types
	for (int i = 0; i < 10; i++) {
		int v = 0;
		glGetIntegerv(params[i], &v);
		gl_log("%s %i\n", names[i], v);
	}
	// others
	int v[2];
	v[0] = v[1] = 0;
	glGetIntegerv(params[10], v);
	gl_log("%s %i %i\n", names[10], v[0], v[1]);
	unsigned char s = 0;
	glGetBooleanv(params[11], &s);
	gl_log("%s %u\n", names[11], (unsigned int)s);
	gl_log("-----------------------------\n");
}

void _print_shader_info_log(GLuint shader_index)
{
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
	glGetShaderInfoLog(shader_index, max_length, &actual_length, log);
	printf("Shader info log for GL index %u: \n%s\n", shader_index, log);
}
void _print_programme_info_log(GLuint programme_index)
{
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
	glGetProgramInfoLog(programme_index, max_length, &actual_length, log);
	printf("Programme info log for GL index %u: \n%s\n", programme_index, log);
}

void print_all_programme_log(GLuint programme) {
	printf("--------------------\nshader programme %i info:\n", programme);
	int params = -1;
	glGetProgramiv(programme, GL_LINK_STATUS, &params);
	printf("GL_LINK_STATUS = %i\n", params);

	glGetProgramiv(programme, GL_ATTACHED_SHADERS, &params);
	printf("GL_ATTACHED_SHADERS = %i\n", params);

	glGetProgramiv(programme, GL_ACTIVE_ATTRIBUTES, &params);
	printf("GL_ACTIVE_ATTRIBUTES = %i\n", params);
	for (GLuint i = 0; i < (GLuint)params; i++) {
		char name[64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveAttrib(programme, i, max_length, &actual_length, &size, &type,
			name);
		if (size > 1) {
			for (int j = 0; j < size; j++) {
				char long_name[64];
				sprintf_s(long_name, "%s[%i]", name, j);
				int location = glGetAttribLocation(programme, long_name);
				printf("  %i) type:%s name:%s location:%i\n", i, glGetString(type),
					long_name, location);
			}
		}
		else {
			int location = glGetAttribLocation(programme, name);
			printf("  %i) type:%s name:%s location:%i\n", i, glGetString(type),
				name, location);
		}
	}
}

bool is_programme_valid(GLuint programme)
{
	glValidateProgram(programme);
	int params = -1;
	glGetProgramiv(programme, GL_VALIDATE_STATUS, &params);
	printf("program %i GL_VALIDATE_STATUS = %i\n", programme, params);
	if (GL_TRUE != params) {
		_print_programme_info_log(programme);
		return false;
	}
	return true;
}
