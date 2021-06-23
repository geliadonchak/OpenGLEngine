#pragma once

#ifndef OPENGLENGINE_ECS_VERTEX_ARRAY_OBJECT_HPP
#define OPENGLENGINE_ECS_VERTEX_ARRAY_OBJECT_HPP

#include <GL/glew.h>

namespace ECS {

class VertexArrayObject {
  public:
    VertexArrayObject() {
        glGenVertexArrays(1, &id);
        bindArray();
    };

    static void linkVertexAttr(GLuint attributeIdx, GLint size, GLenum type, GLboolean isNormalise, GLsizei stride, const GLvoid *pointer) {
        glVertexAttribPointer(attributeIdx, size, type, isNormalise, stride, pointer);
        glEnableVertexAttribArray(attributeIdx);
    };

    void bindArray() const {
        glBindVertexArray(id);
    };

    void deleteArray() const {
        glDeleteVertexArrays(1, &id);
    }

  private:
    unsigned int id{};
};

}

#endif  // OPENGLENGINE_ECS_VERTEX_ARRAY_OBJECT_HPP
