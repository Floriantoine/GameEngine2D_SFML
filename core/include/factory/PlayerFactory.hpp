#pragma once

#include "Components.hpp"
#include "Systems.hpp"
#include "component/ComponentManager.hpp"
#include "observer/ObserverManager.hpp"
#include "system/SystemManager.hpp"

namespace factory {

class PlayerFactory {
  private:
    ObserverManager &_observerManager;
    rtype::ComponentManager &_componentManager;
    rtype::SystemManager &_systemManager;

  public:
    PlayerFactory(ObserverManager &observerManager,
        rtype::ComponentManager &componentManager,
        rtype::SystemManager &systemManager);
    ~PlayerFactory();
    void createPlayer(std::string path, int id);

    void init();
};

} // namespace factory