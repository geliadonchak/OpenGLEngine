#pragma once

#ifndef OPENGLENGINE_SHADER_LOADER_HPP
#define OPENGLENGINE_SHADER_LOADER_HPP

#include <string>
#include <GL/glew.h>

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path, const char* geometry_file_path);

#endif  // OPENGLENGINE_SHADER_LOADER_HPP
