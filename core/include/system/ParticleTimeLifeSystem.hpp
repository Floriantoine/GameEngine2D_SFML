
#pragma once

#include "../components/HealthComponent.hpp"
#include "ASystem.hpp"
#include "tools/Chrono.hpp"
#include "tools/random.hpp"

namespace rtype {

class ParticleTimeLifeSystem : public ASystem {
  public:
    ParticleTimeLifeSystem() : ASystem(){};
    ~ParticleTimeLifeSystem() = default;
    long _elapsedtime = 0;

    void update(long elapsedTime) override
    {
        tools::Chrono::start();

        this->_elapsedtime += elapsedTime;
        if (this->_elapsedtime >= 16) {
            auto array = this->componentManager_
                             ->getComponentList<components::LifeTime>();
            for (auto &it: array) {
                components::HealthComponent *healthC =
                    this->componentManager_
                        ->getComponent<components::HealthComponent>(it.first);
                if (healthC == nullptr)
                    continue;
                if (healthC->health > 0) {
                    healthC->health -= elapsedTime;
                }
            }
            this->_elapsedtime = 0;
        }
        tools::Chrono::end("ParticleTimeLifeSystem");
    };

  private:
    void destroyEntity(Entity *entity) const
    {
        // entity->getEntityManager()->destroyEntity(entity->getId());
    }
};
} // namespace rtype
