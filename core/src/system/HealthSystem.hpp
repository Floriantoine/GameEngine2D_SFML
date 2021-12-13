/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** HealthSystem
*/

#pragma once

#include "../components/HealthComponent.hpp"
#include "./ASystem.hpp"

namespace rtype {

class HealthSystem : public ASystem {
  public:
    HealthSystem() : ASystem(){};
    ~HealthSystem() = default;

    void update(long elapsedTime) override
    {
        this->componentManager_->apply<HealthComponent>(
            [&](HealthComponent *component) {
                if (component->health <= 0) {
                    component->health = component->_initHealth;
                    // this->destroyEntity(component->getEntity());
                } else {
                    component->health -= elapsedTime;
                }
            });
    };

  private:
    void destroyEntity(Entity *entity) const
    {
        // entity->getEntityManager()->destroyEntity(entity->getId());
    }
};
} // namespace rtype
