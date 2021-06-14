#pragma once

#ifndef OPENGLENGINE_SHADER_LOADER_CPP
#define OPENGLENGINE_SHADER_LOADER_CPP

#include "ShaderLoader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path, const char* geometry_file_path) {
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint geometry_shader_id = glCreateShader(GL_GEOMETRY_SHADER);

    std::string vertex_shader_code;
    std::ifstream vertex_shader_stream(vertex_file_path, std::ios::in);
    if (vertex_shader_stream.is_open()) {
        std::stringstream sstr;
        sstr << vertex_shader_stream.rdbuf();
        vertex_shader_code = sstr.str();
        vertex_shader_stream.close();
    } else {
        std::cout << "Can not open: " + (std::string)vertex_file_path << std::endl;
        return 0;
    }

    std::string fragment_shader_code;
    std::ifstream fragment_shader_stream(fragment_file_path, std::ios::in);
    if (fragment_shader_stream.is_open()) {
        std::stringstream sstr;
        sstr << fragment_shader_stream.rdbuf();
        fragment_shader_code = sstr.str();
        fragment_shader_stream.close();
    } else {
        std::cout << "Can not open: " + (std::string)fragment_file_path << std::endl;
        return 0;
    }

    std::string geometry_shader_code;
    if (geometry_file_path != nullptr) {
        std::ifstream geometry_shader_stream(geometry_file_path, std::ios::in);
        if (geometry_shader_stream.is_open()) {
            std::stringstream sstr;
            sstr << geometry_shader_stream.rdbuf();
            geometry_shader_code = sstr.str();
            geometry_shader_stream.close();
        } else {
            std::cout << "Can not open: " + (std::string)geometry_file_path << std::endl;
            return 0;
        }
    }

    GLint result = GL_FALSE;
    int info_log_length;

    std::cout << "Compiling shader: " + (std::string)vertex_file_path << std::endl;
    char const* vertex_source_pointer = vertex_shader_code.c_str();
    glShaderSource(vertex_shader_id, 1, &vertex_source_pointer, nullptr);
    glCompileShader(vertex_shader_id);

    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        std::vector<char> vertex_shader_error_message(info_log_length + 1);
        glGetShaderInfoLog(vertex_shader_id, info_log_length, nullptr, &vertex_shader_error_message[0]);
        std::cout << &vertex_shader_error_message[0] << std::endl;
    }

    std::cout << "Compiling shader: " + (std::string)fragment_file_path << std::endl;
    char const* fragment_source_pointer = fragment_shader_code.c_str();
    glShaderSource(fragment_shader_id, 1, &fragment_source_pointer, nullptr);
    glCompileShader(fragment_shader_id);

    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        std::vector<char> fragment_shader_error_message(info_log_length + 1);
        glGetShaderInfoLog(fragment_shader_id, info_log_length, nullptr, &fragment_shader_error_message[0]);
        std::cout << &fragment_shader_error_message[0] << std::endl;
    }

    if (geometry_file_path != nullptr) {
        std::cout << "Compiling shader: " + (std::string) geometry_file_path << std::endl;
        char const *geometry_source_pointer = geometry_shader_code.c_str();
        glShaderSource(geometry_shader_id, 1, &geometry_source_pointer, nullptr);
        glCompileShader(geometry_shader_id);

        glGetShaderiv(geometry_shader_id, GL_COMPILE_STATUS, &result);
        glGetShaderiv(geometry_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
        if (info_log_length > 0) {
            std::vector<char> geometry_shader_error_message(info_log_length + 1);
            glGetShaderInfoLog(geometry_shader_id, info_log_length, nullptr, &geometry_shader_error_message[0]);
            std::cout << &geometry_shader_error_message[0] << std::endl;
        }
    }

    std::cout << "Linking program\n";
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    if (geometry_file_path != nullptr) {
        glAttachShader(program_id, geometry_shader_id);
    }
    glLinkProgram(program_id);

    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        std::vector<char> program_error_message(info_log_length + 1);
        glGetProgramInfoLog(program_id, info_log_length, nullptr, &program_error_message[0]);

        std::cout << &program_error_message[0] << std::endl;
    }

    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);
    if (geometry_file_path != nullptr) {
        glDetachShader(program_id, geometry_shader_id);
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
    if (geometry_file_path != nullptr) {
        glDeleteShader(geometry_shader_id);
    }

    return program_id;
}

#endif  // OPENGLENGINE_SHADER_LOADER_CPP
