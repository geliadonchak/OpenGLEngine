#pragma once

#include "shaderLoader.hpp"

class Shader {
public:
    Shader(std::string &vertex_path, std::string &fragment_path) {
        shader_id = LoadShaders(vertex_path, fragment_path);
    }

    void use() const {
        glUseProgram(shader_id);
    }

    void set_mat4(const GLchar *name, const Matrix &data) const {
        glm::mat4 glm_matrix = matrix_to_glm(data);
        glUniformMatrix4fv(glGetUniformLocation(shader_id, name), 1, GL_FALSE, &glm_matrix[0][0]);
    }

private:
    GLuint shader_id;

    static glm::mat4 matrix_to_glm(const Matrix &data) {
        return {
                data[0][0], data[0][1], data[0][2], data[0][3],
                data[1][0], data[1][1], data[1][2], data[1][3],
                data[2][0], data[2][1], data[2][2], data[2][3],
                data[3][0], data[3][1], data[3][2], data[3][3]
        };
    }
};