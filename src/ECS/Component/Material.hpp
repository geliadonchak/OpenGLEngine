#pragma once

#ifndef OPENGLENGINE_ECS_COMPONENT_MATERIAL_COMPONENT_HPP
#define OPENGLENGINE_ECS_COMPONENT_MATERIAL_COMPONENT_HPP

#include "IComponent.hpp"

namespace ECS {
namespace Components {

class Material : public IComponent {
  public:
    Material() : IComponent(ECS::Components::MATERIAL_COMPONENT) {}

    Material(int diffuse_, int specular_, float shininess_) : IComponent(ECS::Components::MATERIAL_COMPONENT),
        diffuse(diffuse_), specular(specular_), shininess(shininess_) {}

    int getDiffuse() const {
        return diffuse;
    }

    void setDiffuse(int diffuse_) {
        diffuse = diffuse_;
    }

    int getSpecular() const {
        return specular;
    }

    void setSpecular(int specular_) {
        specular = specular_;
    }

    float getShininess() const {
        return shininess;
    }

    void setShininess(float shininess_) {
        shininess = shininess_;
    }

  private:
    int diffuse = 0;
    int specular = 0;
    float shininess = 0.f;
};

}
}

#endif // OPENGLENGINE_ECS_COMPONENT_MATERIAL_COMPONENT_HPP