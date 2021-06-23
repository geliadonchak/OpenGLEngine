#pragma once

#ifndef OPENGLENGINE_ECS_COMPONENT_TEXTURE_COMPONENT_HPP
#define OPENGLENGINE_ECS_COMPONENT_TEXTURE_COMPONENT_HPP

#include "IComponent.hpp"

namespace ECS {
namespace Components {

class Texture : public IComponent {
  public:
    Texture() : IComponent(ECS::Components::TEXTURE_COMPONENT) {}

    explicit Texture(const std::vector<std::string>& faces_): IComponent(ECS::Components::TEXTURE_COMPONENT),
        faces(faces_) {}

    unsigned int getTextureId() const {
        return textureId;
    }

    void setTextureId(const GLuint &textureId_) {
        textureId = textureId_;
    }

    std::string &getType() const {
        return type;
    }

    void setType(const std::string &type_) {
        Texture::type = type_;
    }

    std::string &getPath() const {
        return path;
    }

    void setPath(const std::string &path_) {
        Texture::path = path_;
    }

    std::vector<std::string> &getFaces() const {
        return faces;
    }

    void setFaces(const std::vector<std::string>& faces_) {
        faces = faces_;
    }

  private:
    GLuint textureId = -1;
    std::string type{};
    std::string path{};
    std::vector<std::string> faces{};
};

}
}

#endif // OPENGLENGINE_ECS_COMPONENT_TEXTURE_COMPONENT_HPP