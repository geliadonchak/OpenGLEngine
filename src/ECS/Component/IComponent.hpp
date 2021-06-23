#pragma once

#ifndef OPENGLENGINE_ECS_COMPONENT_ICOMPONENT_HPP
#define OPENGLENGINE_ECS_COMPONENT_ICOMPONENT_HPP

namespace ECS {
namespace Components {

enum ComponentTypes {
    TEXTURE_COMPONENT,
    MATERIAL_COMPONENT,
    SHADER_COMPONENT,
};

class IComponent {
  public:
    explicit IComponent(ComponentTypes type): componentType(type) {}

    virtual ComponentTypes getComponentType() const {
        return componentType;
    }

  private:
    ComponentTypes componentType;
};

}
}

#endif // OPENGLENGINE_ECS_COMPONENT_ICOMPONENT_HPP