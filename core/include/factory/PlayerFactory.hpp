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
    fa::ComponentManager &_componentManager;
    fa::SystemManager &_systemManager;

  public:
    PlayerFactory(ObserverManager &observerManager,
        fa::ComponentManager &componentManager,
        fa::SystemManager &systemManager);
    ~PlayerFactory();
    void createPlayer(std::string path, int id);

    void init();
};

} // namespace factory