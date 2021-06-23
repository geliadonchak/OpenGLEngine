#pragma once

#ifndef OPENGLENGINE_ECS_COMPONENT_MATERIAL_COMPONENT_HPP
#define OPENGLENGINE_ECS_COMPONENT_MATERIAL_COMPONENT_HPP

#include <string>
#include <utility>
#include <GL/gl.h>
#include "IComponent.hpp"

namespace ECS {
namespace Components {

class Shader : public IComponent {
  public:
    Shader(std::string vertexPath_, std::string fragmentPath_) :
        IComponent(SHADER_COMPONENT), vertexPath(std::move(vertex_path_)), fragmentPath(std::move(fragment_path_)) {}

    const std::string &getVertexPath() const {
        return vertexPath;
    }

    void setVertexPath(const std::string &vertexPath_) {
        vertexPath = vertexPath_;
    }

    const std::string &getFragmentPath() const {
        return fragmentPath;
    }

    void setFragmentPath(const std::string &fragmentPath_) {
        fragmentPath = fragmentPath_;
    }

    const GLuint &getShaderId() const {
        return shaderId;
    }

    void setShaderId(const GLuint &shader_id) {
        shaderId = shader_id;
    }

  private:
    std::string vertexPath{};
    std::string fragmentPath{};
    GLuint shaderId = 0;
};

}
}

#endif // OPENGLENGINE_ECS_COMPONENT_MATERIAL_COMPONENT_HPP