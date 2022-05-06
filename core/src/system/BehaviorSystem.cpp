#include "system/BehaviorSystem.hpp"
#include "Game.hpp"

namespace systems {

void BehaviorSystem::update(long elapsedTime)
{
    Game::Game::getComponentManager().apply<components::BehaviorComponent>(
        [&](components::BehaviorComponent *component) {
            if (component != nullptr) {
                if (component->isInit == false) {
                    component->_behavior.Start();
                    component->isInit = true;
                } else {
                    component->_behavior.Update();
                }
            }
        });
};
} // namespace systems