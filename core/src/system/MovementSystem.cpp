#include "system/MovementSystem.hpp"
#include "components/PosComponent.hpp"
#include "components/TargetEntity.hpp"
#include "components/systemActivator/LinearMovement.hpp"
#include <algorithm>
#include <math.h>

namespace systems {
void MovementSystem::update(long elapsedTime)
{
    this->_elapsedTime += elapsedTime;
    if (this->_elapsedTime >= 16) {
        auto array = this->_componentManager
                         ->getComponentList<components::LinearMovement>();
        for (auto &it: array) {
            components::LinearMovement *linearC =
                static_cast<components::LinearMovement *>(it.second);
            if (linearC == nullptr)
                continue;
            if (linearC->_direction != "") {
                components::PosComponent *posC =
                    this->_componentManager
                        ->getComponent<components::PosComponent>(it.first);
                if (!posC)
                    continue;
                float steep = 0.5 * _elapsedTime;
                if (linearC->_direction == "left")
                    posC->_pos.x -= steep;
                if (linearC->_direction == "right")
                    posC->_pos.x += steep;
                if (linearC->_direction == "up")
                    posC->_pos.y -= steep;
                if (linearC->_direction == "down")
                    posC->_pos.y += steep;
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
            // float pow1 = 0;
            // float pow2 = 0;
            // if (targetPosC->_pos.x < posC->_pos.x) {
            //     pow1 = pow((posC->_pos.x - targetPosC->_pos.x), 2);
            // } else {
            //     pow1 = pow((targetPosC->_pos.x - posC->_pos.x), 2);
            // }
            // if (targetPosC->_pos.y < posC->_pos.y) {
            //     pow2 = pow((posC->_pos.y - targetPosC->_pos.y), 2);
            // } else {
            //     pow2 = pow((targetPosC->_pos.y - posC->_pos.y), 2);
            // }
            // float dist = sqrt(pow1 + pow2);
            // float steep = dist / (0.5 * _elapsedTime);
            // if (steep < 1)
            //     steep = 1;
            float steep = (0.5 * _elapsedTime);
            components::LinearMovement *linearC =
                this->_componentManager
                    ->getComponent<components::LinearMovement>(it.first);
            if (linearC == nullptr) {
                if (targetPosC->_pos.x - 10 > posC->_pos.x) {
                    posC->_pos.x += steep;
                }
                if (targetPosC->_pos.x + 10 < posC->_pos.x) {
                    posC->_pos.x -= steep;
                }
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