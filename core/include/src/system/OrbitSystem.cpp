#include "system/OrbitSystem.hpp"
#include "components/PosComponent.hpp"
#include "components/TargetEntity.hpp"
#include "components/systemActivator/Orbit.hpp"

namespace systems {
void OrbitSystem::update(long elapsedTime)
{
    this->_elapsedTime += elapsedTime;
    if (this->_elapsedTime >= 16) {
        auto array =
            this->_componentManager->getComponentList<components::Orbit>();
        for (auto &it: array) {
            components::Orbit *orbitC =
                static_cast<components::Orbit *>(it.second);
            components::PosComponent *PosC =
                this->_componentManager->getComponent<components::PosComponent>(
                    it.first);
            if (!PosC || !orbitC)
                continue;
            components::TargetEntity *targetC =
                this->_componentManager->getComponent<components::TargetEntity>(
                    it.first);
            if (targetC) {
                components::PosComponent *posTargetC =
                    this->_componentManager
                        ->getComponent<components::PosComponent>(
                            targetC->_target);
                if (posTargetC)
                    orbitC->_pivotPoint = posTargetC->_pos;
            }

            orbitC->_angle += 0.1;
            if (orbitC->_angle >= 360)
                orbitC->_angle = 0;

            PosC->_pos.x =
                (orbitC->_pivotPoint.x + orbitC->_radius * cos(orbitC->_angle));
            PosC->_pos.y =
                (orbitC->_pivotPoint.y + orbitC->_radius * sin(orbitC->_angle));
        }

        this->_elapsedTime = 0;
    }
}
} // namespace systems