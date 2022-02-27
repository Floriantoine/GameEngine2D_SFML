#include "system/CollisionDamage.hpp"

namespace systems {

void CollisionDamage::update(long elapsedTime)
{
    auto array = this->_componentManager
                     ->getComponentList<components::HaveCollisionDamage>();
    for (auto &it: array) {
        components::SolidBlock *solidC =
            this->_componentManager->getComponent<components::SolidBlock>(
                it.first);
        if (solidC) {
            if (solidC->_haveCollision) {
                components::Damage *damageC =
                    this->_componentManager->getComponent<components::Damage>(
                        solidC->_targetId);
                if (damageC) {
                    components::HealthComponent *healthC =
                        this->_componentManager
                            ->getComponent<components::HealthComponent>(
                                it.first);
                    if (healthC) {
                        healthC->health -= damageC->_damage;
                    }
                }
            }
        }
    }
};
} // namespace systems