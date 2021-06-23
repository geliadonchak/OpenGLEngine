#pragma once

#ifndef OPENGLENGINE_ECS_SHADER_HPP
#define OPENGLENGINE_ECS_SHADER_HPP

#include <GL/glew.h>
#include <fstream>

class Shader {
  public:
    Shader(const std::string& vertex_path, const std::string& fragment_path) {
        loadShaders(vertex_path, fragment_path);
    }

    void use() const {
        glUseProgram(shaderId);
    }

    void set_mat4(const std::string &name, const Matrix &data) const {
        glm::mat4 glm_matrix = matrix2glm(data);
        glUniformMatrix4fv(glGetUniformLocation(shaderId, &name[0]), 1, GL_FALSE, &glm_matrix[0][0]);
    }

    void set_vec3(const std::string &name, const Vector &value) const {
        glUniform3fv(glGetUniformLocation(shaderId, &name[0]), 1, &value[0]);
    }

    void set_vec3(const std::string &name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(shaderId, &name[0]), x, y, z);
    }

    void set_float(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(shaderId, &name[0]), value);
    }

    void set_int(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(shaderId, &name[0]), value);
    }

    GLuint getShaderId() const {
        return shaderId;
    }

  private:
    GLuint shaderId = 0;

    static glm::mat4 matrix2glm(const Matrix &data) {
        return {
            data[0][0], data[0][1], data[0][2], data[0][3],
            data[1][0], data[1][1], data[1][2], data[1][3],
            data[2][0], data[2][1], data[2][2], data[2][3],
            data[3][0], data[3][1], data[3][2], data[3][3]
        };
    }

    void loadShaders(const std::string &vertexFilePath, const std::string &fragmentFilePath) {
        GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

        std::string vertexShaderCode;
        std::ifstream vertexShaderStream(vertexFilePath, std::ios::in);
        if (vertexShaderStream.is_open()) {
            std::stringstream sstream;
            sstream << vertexShaderStream.rdbuf();
            vertexShaderCode = sstream.str();
            vertexShaderStream.close();
        } else {
            std::cerr << "Can't open: " + vertexFilePath << std::endl;
            return;
        }

        std::string fragmentShaderCode;
        std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);
        if (fragmentShaderStream.is_open()) {
            std::stringstream sstr;
            sstr << fragmentShaderStream.rdbuf();
            fragmentShaderCode = sstr.str();
            fragmentShaderStream.close();
        }

        GLint result = GL_FALSE;
        int infoLogLength;

        std::cout << "Compiling shader: " + vertexFilePath << std::endl;
        char const *vertexSourcePointer = vertexShaderCode.c_str();
        glShaderSource(vertexShaderId, 1, &vertexSourcePointer, nullptr);
        glCompileShader(vertexShaderId);

        glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
        glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            std::vector<char> errorMsg(infoLogLength + 1);
            glGetShaderInfoLog(vertexShaderId, infoLogLength, nullptr, &errorMsg[0]);
            std::cout << &errorMsg[0] << std::endl;
        }

        std::cout << "Compiling shader: " + fragmentFilePath << std::endl;
        char const *fragmentSourcePointer = fragmentShaderCode.c_str();
        glShaderSource(fragmentShaderId, 1, &fragmentSourcePointer, nullptr);
        glCompileShader(fragmentShaderId);

        glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &result);
        glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            std::vector<char> errorMsg(infoLogLength + 1);
            glGetShaderInfoLog(fragmentShaderId, infoLogLength, nullptr, &errorMsg[0]);
            std::cerr << &errorMsg[0] << std::endl;
        }

        std::cout << "Linking program\n";
        GLuint programId = glCreateProgram();
        glAttachShader(programId, vertexShaderId);
        glAttachShader(programId, fragmentShaderId);
        glLinkProgram(programId);

        glGetProgramiv(programId, GL_LINK_STATUS, &result);
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            std::vector<char> errorMsg(infoLogLength + 1);
            glGetProgramInfoLog(programId, infoLogLength, nullptr, &errorMsg[0]);

            std::cerr << &errorMsg[0] << std::endl;
        }

        glDetachShader(programId, vertexShaderId);
        glDetachShader(programId, fragmentShaderId);

        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

        shaderId = programId;
    }
};

#endif  // OPENGLENGINE_ECS_SHADER_HPP
