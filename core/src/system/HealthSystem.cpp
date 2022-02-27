#include "system/HealthSystem.hpp"

namespace systems {
void HealthSystem::update(long elapsedTime)
{
    this->_elapsedTime += elapsedTime;
    if (this->_elapsedTime >= 16) {
        auto array = this->_componentManager
                         ->getComponentList<components::HealthComponent>();
        for (auto &it: array) {
            components::HealthComponent *lifeC =
                static_cast<components::HealthComponent *>(it.second);
            if (lifeC == nullptr)
                continue;
            if (lifeC->health <= 0) {
                components::LoopLife *loopC =
                    this->_componentManager->getComponent<components::LoopLife>(
                        it.first);
                if (!loopC)
                    this->_componentManager->removeAllComponents(it.first);
            }
        }
        this->_elapsedTime = 0;
    }
}
} // namespace systems