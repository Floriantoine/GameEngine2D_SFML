#pragma once

#include "ASystem.hpp"
#include "components/HealthComponent.hpp"

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
