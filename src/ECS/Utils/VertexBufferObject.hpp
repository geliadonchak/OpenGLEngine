#pragma once

#ifndef OPENGLENGINE_ECS_VERTEX_BUFFER_OBJECT_HPP
#define OPENGLENGINE_ECS_VERTEX_BUFFER_OBJECT_HPP

#include <GL/glew.h>

namespace ECS {

class VertexBufferObject {
 public:
    explicit VertexBufferObject(float* vertices, size_t verticesSize) {
        glGenBuffers(1, &id);
        bindBuffer();
        glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    };

    void bindBuffer() const {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    };

    void deleteBuffer() {
        glDeleteBuffers(1, &id);
    }

 private:
    unsigned int id{};
};

}

#endif  // OPENGLENGINE_ECS_VERTEX_BUFFER_OBJECT_HPP
