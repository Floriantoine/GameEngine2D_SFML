#include "system/HealthSystem.hpp"

namespace systems {
void HealthSystem::update(long elapsedTime)
{
    this->_elapsedtime += elapsedTime;
    if (this->_elapsedtime >= 16) {
        auto array = this->componentManager_
                         ->getComponentList<components::HealthComponent>();
        for (auto &it: array) {
            components::HealthComponent *lifeC =
                static_cast<components::HealthComponent *>(it.second);
            if (lifeC == nullptr)
                continue;
            if (lifeC->health <= 0) {
                components::LoopLife *loopC =
                    this->componentManager_->getComponent<components::LoopLife>(
                        it.first);
                if (!loopC)
                    this->componentManager_->removeAllComponents(it.first);
            }
        }
        this->_elapsedtime = 0;
    }
}
} // namespace systems