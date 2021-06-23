#pragma once

#ifndef OPENGLENGINE_ECS_SYSTEM_ISYSTEM_HPP
#define OPENGLENGINE_ECS_SYSTEM_ISYSTEM_HPP

#include <memory>
#include "../Component/IComponent.hpp"
#include "../InputSystem/InputEvent.hpp"

namespace ECS {
namespace System {

class ISystem {
  public:
    explicit ISystem(std::shared_ptr<Component> component_) {
        component = component_;
    }

    const Component *&getComponent() const {
        return component.get();
    }

    virtual void onLoad() = {};
    virtual void onUpdate() = {};
    virtual void onEnable() = {};
    virtual void onDisable() = {};

  private:
    std::shared_ptr<Component> component{};
};

}
}

#endif // OPENGLENGINE_ECS_SYSTEM_ISYSTEM_HPP