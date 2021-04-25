#pragma once

#ifndef OPENGLENGINE_SHADER_LOADER_HPP
#define OPENGLENGINE_SHADER_LOADER_HPP

#include <string>
#include <GL/glew.h>

GLuint LoadShaders(const std::string vertex_file_path, const std::string fragment_file_path);

#endif //OPENGLENGINE_SHADER_LOADER_HPP