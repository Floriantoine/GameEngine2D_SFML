#include "system/CollisionDamage.hpp"

namespace systems {

void CollisionDamage::update(long elapsedTime)
{
    auto array = this->componentManager_
                     ->getComponentList<components::HaveCollisionDamage>();
    for (auto it = array.begin(); it != array.end(); ++it) {
        components::SolidBlock *solidC =
            this->componentManager_->getComponent<components::SolidBlock>(
                it->first);
        if (solidC) {
            if (solidC->_haveCollision) {
                components::Damage *damageC =
                    this->componentManager_->getComponent<components::Damage>(
                        solidC->_targetId);
                if (damageC) {
                    components::HealthComponent *healthC =
                        this->componentManager_
                            ->getComponent<components::HealthComponent>(
                                it->first);
                    if (healthC) {
                        healthC->health -= damageC->_damage;
                        std::cout << "life: " << healthC->health << std::endl;
                    }
                }
            }
        }
    }
};
} // namespace systems