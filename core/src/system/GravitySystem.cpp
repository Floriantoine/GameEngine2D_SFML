#include "system/GravitySystem.hpp"
#include "components/ForceComponent.hpp"
#include "components/MasseComponent.hpp"
#include "components/PosComponent.hpp"
#include "components/RigideBody.hpp"
#include "components/SolidBlock.hpp"
#include "tools/Chrono.hpp"

namespace systems {

void GravitySystem::ExplicitEuler(int N, std::vector<sf::Vector2f> *cur_S,
    std::vector<sf::Vector2f> prior_S, std::vector<sf::Vector2f> S_derivs,
    float delta_t)
{
    for (int i = 0; i < N; i++) {
        (*cur_S)[i] =
            prior_S[i] + (delta_t * (_elapsedTime / 16.0f)) * S_derivs[i];
    }
}

void GravitySystem::update(long elapsedTime)
{
    tools::Chrono::start();

    this->_elapsedTime += elapsedTime;
    if (this->_elapsedTime >= 16) {
        auto arrayCollision =
            this->_componentManager->getComponentList<components::SolidBlock>();
        std::unordered_map<fa::id_t, components::SolidBlock> collisionVector;
        for (auto &collisionComp: arrayCollision) {
            components::SolidBlock *solidBlockComp =
                static_cast<components::SolidBlock *>(collisionComp.second);
            if (solidBlockComp != nullptr) {
                collisionVector[collisionComp.first] = *solidBlockComp;
            }
        }

        auto array =
            this->_componentManager->getComponentList<components::RigideBody>();
        for (auto &it: array) {
            components::RigideBody *gravityC =
                static_cast<components::RigideBody *>(it.second);
            if (gravityC == nullptr)
                continue;
            components::PosComponent *PosC =
                this->_componentManager->getComponent<components::PosComponent>(
                    it.first);
            if (PosC == nullptr) {
                continue;
            }

            components::MasseComponent *MasseComponent =
                this->_componentManager
                    ->getComponent<components::MasseComponent>(it.first);

            components::ForceComponent *forceComponent =
                this->_componentManager
                    ->getComponent<components::ForceComponent>(it.first);

            if (collisionVector.size() > 0) {
                auto collision = collisionVector.find(it.first);
                if (forceComponent != nullptr &&
                    collision != collisionVector.end()) {
                    components::SolidBlock collitionFirst =
                        static_cast<components::SolidBlock>(collision->second);
                    if (collitionFirst._haveCollision == true &&
                        collitionFirst._targetsId.size() > 0) {
                        for (auto &idTarget: collitionFirst._targetsId) {
                            components::ForceComponent *forceSecond =
                                this->_componentManager
                                    ->getComponent<components::ForceComponent>(
                                        idTarget);
                            components::RigideBody *gravitySecond =
                                this->_componentManager
                                    ->getComponent<components::RigideBody>(
                                        idTarget);
                            if (forceSecond != nullptr &&
                                gravitySecond != nullptr) {
                                sf::Vector2f forceTempo = forceSecond->force;
                                forceSecond->force = forceComponent->force;
                                forceComponent->force = forceTempo;
                                sf::Vector2f gravityTempo =
                                    gravitySecond->_cur_S;
                                gravitySecond->_cur_S = gravityC->_cur_S;
                                gravityC->_cur_S = gravityTempo;
                            } else {
                                forceComponent->force = -forceComponent->force;
                                if (gravityC->_cur_S.y > 0) {
                                    gravityC->_cur_S = -gravityC->_cur_S;
                                }
                                gravityC->_cur_S.y = 0;
                                // gravityC->_cur_S.y = std::min(-1.0f,
                                //     gravityC->_cur_S.y +
                                //         10 * (MasseComponent != nullptr
                                //                      ? MasseComponent->masse
                                //                      : 1));
                            }

                            auto collisionTarget =
                                collisionVector.find(idTarget);
                            if (collisionTarget != collisionVector.end()) {
                                auto targetCollisionIter = std::find(
                                    collisionTarget->second._targetsId.begin(),
                                    collisionTarget->second._targetsId.end(),
                                    it.first);
                                if (targetCollisionIter !=
                                    collisionTarget->second._targetsId.end()) {
                                    collisionTarget->second._targetsId.erase(
                                        targetCollisionIter);
                                }
                            }
                        }
                    }
                    collisionVector.erase(it.first);
                }
            }

            sf::Vector2f _prior_S0 = gravityC->_cur_S;
            sf::Vector2f force =
                (forceComponent ? forceComponent->force : sf::Vector2f(0, 0));
            sf::Vector2f _S_derivs0 =
                (gravityC->_haveGravity ? (force + sf::Vector2f(0, 9.81))
                                        : force);
            sf::Vector2f _S_derivs1(0, 0);
            if (MasseComponent) {
                _S_derivs1 = _prior_S0 / (float)(MasseComponent->masse != 0
                                                     ? MasseComponent->masse
                                                     : 1.0f);
            }

            float delta = delta_t * (_elapsedTime / 16.0f);
            gravityC->_cur_S = _prior_S0 + delta * _S_derivs0;
            PosC->_pos = PosC->_pos + delta * _S_derivs1;

            // ExplicitEuler(gravityC->_cur_S.size(), &gravityC->_cur_S,
            //     gravityC->_prior_S, gravityC->_S_derivs, delta_t);
        }

        this->_elapsedTime = 0;
    }
    tools::Chrono::end("gravity");
}
} // namespace systems