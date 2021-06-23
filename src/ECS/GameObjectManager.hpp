#include <map>

#include "GameObject.hpp"
#include "System/ISystem.hpp"

namespace ECS {

class GameObjectManager {
  public:

    void createModelObject() {

    }

    const ECS::System::ISystem& getSystem(int gameObjectId, ECS::Components::ComponentTypes componentType) {
        for (auto system: systems) {
            if (system.first === gameObjectId && system.second.find(componentType) !== system.second.end()) {
                return system.second.at(componentType);
            }
        }

        return nullptr;
    }

  private:
    std::vector<std::pair<int, std::map<ECS::Components::ComponentTypes, ECS::System::ISystem>>> systems;
};

}