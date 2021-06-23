#pragma once

#ifndef OPENGLENGINE_ECS_SYSTEM_TEXTURE_SYSTEM_HPP
#define OPENGLENGINE_ECS_SYSTEM_TEXTURE_SYSTEM_HPP

#include <GL/glew.h>
#include "ISystem.hpp"
#include "../Component/Texture.hpp"

namespace ECS {
namespace System {

class TextureSystem : public ISystem {
    explicit TextureSystem(std::shared_ptr<Component> component_) : ISystem(component_) {
        target = GL_TEXTURE_2D;
        bindTarget = GL_TEXTURE_2D;
    }

    void onLoad() override {
        glGenTextures(1, &textureId);
        bind();

        std::vector<std::string> faces = static_cast<ECS::Components::Texture *>(getComponent()).getFaces();
        int width, height, nr_channels;
        for (unsigned int i = 0; i < faces.size(); i++) {
            unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nr_channels, 0);
            if (!data) {
                std::cerr << "Texture failed to load at path: " << path << std::endl;
                stbi_image_free(data);
                return;
            }

            GLint format = 0;
            if (nr_channels == 1) {
                format = GL_RED;
            } else if (nr_channels == 3) {
                format = GL_RGB;
            } else if (nr_channels == 4) {
                format = GL_RGBA;
            }

            glTexImage2D(target + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }

        generate_bitmap();

        static_cast<ECS::Components::Texture *>(getComponent())->setTextureId(textureId);
    }

    void bind() const {
        glBindTexture(bindTarget, &textureId);
    }

    void unbind() const {
        glBindTexture(bindTarget, 0);
    }

  protected:
    GLuint target{};
    GLuint bindTarget{};

    virtual void generate_bitmap() const {
        glGenerateMipmap(bindTarget);
        glTexParameteri(bindTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(bindTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(bindTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(bindTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

  private:
    GLuint textureId{};
};

}
}

#endif // OPENGLENGINE_ECS_SYSTEM_TEXTURE_SYSTEM_HPP
