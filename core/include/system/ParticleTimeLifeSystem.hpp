
#pragma once

#include "../components/HealthComponent.hpp"
#include "ASystem.hpp"
#include "tools/random.hpp"

namespace rtype {

class ParticleTimeLifeSystem : public ASystem {
  public:
    ParticleTimeLifeSystem() : ASystem(){};
    ~ParticleTimeLifeSystem() = default;

    void update(long elapsedTime) override
    {
        this->componentManager_->apply<components::HealthComponent>(
            [&](components::HealthComponent *component) {
                if (component->health > 0) {
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
