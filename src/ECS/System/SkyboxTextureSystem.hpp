#pragma once

#ifndef OPENGLENGINE_ECS_SYSTEM_SKYBOX_TEXTURE_SYSTEM_HPP
#define OPENGLENGINE_ECS_SYSTEM_SKYBOX_TEXTURE_SYSTEM_HPP

#include "TextureSystem.hpp"

namespace ECS {
namespace System {

class SkyboxTextureSystem : TextureSystem {
  public:
    explicit SkyboxTextureSystem(const std::shared_ptr<ECS::Components::IComponent>& component_) : TextureSystem(component_) {
        target = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
        bindTarget = GL_TEXTURE_CUBE_MAP;
    }

  protected:
    void generate_bitmap() const override {
        glGenerateMipmap(bindTarget);
        glTexParameteri(bindTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(bindTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(bindTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(bindTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(bindTarget, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }
};

}
}

#endif // OPENGLENGINE_ECS_SYSTEM_SKYBOX_TEXTURE_SYSTEM_HPP