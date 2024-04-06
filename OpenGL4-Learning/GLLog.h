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

#endif
