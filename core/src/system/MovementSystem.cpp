#include "system/MovementSystem.hpp"
#include "components/Direction.hpp"
#include "components/PosComponent.hpp"
#include "components/Speed.hpp"
#include "components/TargetEntity.hpp"
#include "components/systemActivator/LinearMovement.hpp"
#include <algorithm>
#include <math.h>

namespace systems {
void MovementSystem::update(long elapsedTime)
{
    this->_elapsedTime += elapsedTime;
    if (this->_elapsedTime >= 16) {
        auto array =
            this->_componentManager->getComponentList<components::Direction>();
        for (auto &it: array) {
            components::Direction *directionC =
                static_cast<components::Direction *>(it.second);
            if (directionC == nullptr)
                continue;
            if (directionC->_direction != directions::STATIC) {
                components::PosComponent *posC =
                    this->_componentManager
                        ->getComponent<components::PosComponent>(it.first);
                components::Speed *speedC =
                    this->_componentManager->getComponent<components::Speed>(
                        it.first);
                if (posC) {
                    float steep = 0.5 * _elapsedTime / 16 *
                                  (speedC != nullptr ? speedC->_speed : 1);
                    posC->_pos.x += directionC->_direction.x * steep;
                    posC->_pos.y += directionC->_direction.y * steep;
                }
                if (directionC->_continuous == false) {
                    directionC->_direction = directions::STATIC;
                }
            }
        }

        auto arrayTarget = this->_componentManager
                               ->getComponentList<components::TargetEntity>();
        for (auto &it: arrayTarget) {
            components::TargetEntity *targetC =
                static_cast<components::TargetEntity *>(it.second);
            if (targetC == nullptr)
                continue;
            components::PosComponent *posC =
                this->_componentManager->getComponent<components::PosComponent>(
                    it.first);
            components::PosComponent *targetPosC =
                this->_componentManager->getComponent<components::PosComponent>(
                    targetC->_target);
            if (!posC || !targetPosC)
                continue;
            components::Speed *speedC =
                this->_componentManager->getComponent<components::Speed>(
                    it.first);
            float steep = (0.5 * _elapsedTime / 16 *
                           (speedC != nullptr ? speedC->_speed : 1));
            if (targetPosC->_pos.x - 10 > posC->_pos.x) {
                posC->_pos.x += steep;
            }
            if (targetPosC->_pos.x + 10 < posC->_pos.x) {
                posC->_pos.x -= steep;
            }
            if (targetPosC->_pos.y - 10 > posC->_pos.y) {
                posC->_pos.y += steep;
            }
            if (targetPosC->_pos.y + 10 < posC->_pos.y) {
                posC->_pos.y -= steep;
            }
        }
        this->_elapsedTime = 0;
    }
}
} // namespace systems