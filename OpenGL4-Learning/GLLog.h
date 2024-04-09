#pragma once
#ifndef GL_LOG
#define GL_LOG

#include <iostream>
#include <time.h>
#include <stdarg.h>
#define GL_LOG_FILE "gl.log"

bool restart_gl_log();
bool gl_log(const char* message, ...);
bool gl_log_err(const char* message, ...);
void log_gl_params();
void _print_shader_info_log(GLuint shader_index);
void _print_programme_info_log(GLuint shader_index);
void print_all_programme_log(GLuint programme);
bool is_programme_valid(GLuint programme);

#endif
