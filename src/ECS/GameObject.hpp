#include <string>
#include <utility>
#include <memory>
#include <vector>

#include "Component/IComponent.hpp"

namespace ECS {

class GameObject {
  public:
    GameObject(std::string name_, std::string tag_, bool enabled_) :
        name(std::move(name_)), tag(std::move(tag_)), enabled(enabled_) {}

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name_) {
        name = name_;
    }

    const std::string &getTag() const {
        return tag;
    }

    void setTag(const std::string &tag_) {
        tag = tag_;
    }

    bool isEnabled() const {
        return enabled;
    }

    void setEnabled(bool enabled_) {
        enabled = enabled_;
    }

    void addComponent(const ECS::Components::IComponent &component) {
        auto iter = components.begin();
        while (iter != components.end() || iter->getComponentType() != component.getComponentType()) {
            iter++;
        }

        if (iter != components.end()) {
            return;
        }

        components.push_back(component);
    }

    void removeComponent(ECS::Components::ComponentTypes type) {
        auto iter = components.begin();
        while (iter != components.end() || iter->getComponentType() != type) {
            iter++;
        }

        if (iter == components.end()) {
            return;
        }

        components.erase(iter);
    }

    const std::vector<ECS::Components::IComponent>& getComponents() {
        return components;
    }

  private:
    std::string name;
    std::string tag;
    bool enabled;

    std::vector<ECS::Components::IComponent> components{};
};

}