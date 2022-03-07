
#pragma once

#include "../components/HealthComponent.hpp"
#include "ASystem.hpp"
#include "tools/Chrono.hpp"
#include "tools/random.hpp"

namespace fa {

class ParticleTimeLifeSystem : public ASystem {
  public:
    ParticleTimeLifeSystem() : ASystem(){};
    ~ParticleTimeLifeSystem() = default;
    long _elapsedTime = 0;

    void update(long elapsedTime) override
    {
        tools::Chrono::start();

        this->_elapsedTime += elapsedTime;
        if (this->_elapsedTime >= 16) {
            auto array = this->_componentManager
                             ->getComponentList<components::LifeTime>();
            for (auto &it: array) {
                components::HealthComponent *healthC =
                    this->_componentManager
                        ->getComponent<components::HealthComponent>(it.first);
                if (healthC == nullptr)
                    continue;
                if (healthC->health > 0) {
                    healthC->health -= elapsedTime;
                }
            }
            this->_elapsedTime = 0;
        }
        tools::Chrono::end("ParticleTimeLifeSystem");
    };

  private:
    void destroyEntity(Entity *entity) const
    {
        // entity->getEntityManager()->destroyEntity(entity->getId());
    }
};
} // namespace fa
