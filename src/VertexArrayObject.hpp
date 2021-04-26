#pragma once

#ifndef OPENGLENGINE_VERTEXARRAYOBJECT_HPP
#define OPENGLENGINE_VERTEXARRAYOBJECT_HPP

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class VertexArrayObject {
 public:
    VertexArrayObject() {
        glGenVertexArrays(1, &ID);
        bind_array();
    };

    static void link_vertex_attr(GLuint attribute_idx, GLint size, GLenum type, GLboolean is_normalise, GLsizei stride, const GLvoid* pointer) {
        glVertexAttribPointer(attribute_idx, size, type, is_normalise, stride, pointer);
        glEnableVertexAttribArray(attribute_idx);
    };

    void bind_array() const {
        glBindVertexArray(ID);
    };

    void delete_array() const {
        glDeleteVertexArrays(1, &ID);
    }

 private:
    unsigned int ID{};
};

#endif //OPENGLENGINE_VERTEXARRAYOBJECT_HPP