#include "system/GravitySystem.hpp"
#include "components/ForceComponent.hpp"
#include "components/GravityComponent.hpp"
#include "components/MasseComponent.hpp"
#include "components/PosComponent.hpp"
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

        auto array =
            this->_componentManager->getComponentList<components::Gravity>();
        for (auto &it: array) {
            components::Gravity *gravityC =
                static_cast<components::Gravity *>(it.second);
            if (gravityC == nullptr)
                continue;
            components::PosComponent *PosC =
                this->_componentManager->getComponent<components::PosComponent>(
                    it.first);
            if (PosC == nullptr) {
                continue;
            }

            components::ForceComponent *forceComponent =
                this->_componentManager
                    ->getComponent<components::ForceComponent>(it.first);
            if (arrayCollision.size() > 0) {
                auto collision = arrayCollision.find(it.first);
                if (forceComponent != nullptr &&
                    collision != arrayCollision.end()) {
                    components::SolidBlock *collitionFirst =
                        static_cast<components::SolidBlock *>(
                            collision->second);
                    if (collitionFirst != nullptr &&
                        collitionFirst->_haveCollision == true &&
                        collitionFirst->_targetId != it.first) {
                        components::ForceComponent *forceSecond =
                            this->_componentManager
                                ->getComponent<components::ForceComponent>(
                                    collitionFirst->_targetId);
                        components::Gravity *gravitySecond =
                            this->_componentManager
                                ->getComponent<components::Gravity>(
                                    collitionFirst->_targetId);
                        if (forceSecond != nullptr &&
                            gravitySecond != nullptr) {
                            sf::Vector2f forceTempo = forceSecond->force;
                            forceSecond->force = forceComponent->force;
                            forceComponent->force = forceTempo;
                            sf::Vector2f gravityTempo = gravitySecond->_cur_S;
                            gravitySecond->_cur_S = gravityC->_cur_S;
                            gravityC->_cur_S = gravityTempo;
                        } else {
                            // forceComponent->force = forceComponent->force;
                            std::cout
                                << "======================================="
                                << std::endl;
                            std::cout << "gravity: " << gravityC->_cur_S.y
                                      << std::endl;
                            if (gravityC->_cur_S.y > 0) {
                                gravityC->_cur_S = -gravityC->_cur_S;
                                std::cout
                                    << "Before gravity: " << gravityC->_cur_S.y
                                    << std::endl;
                            }
                            gravityC->_cur_S.y =
                                std::min(0.0f, gravityC->_cur_S.y + 10);
                            std::cout << "After gravity: " << gravityC->_cur_S.y
                                      << std::endl;
                            std::cout
                                << "======================================="
                                << std::endl;
                        }
                        arrayCollision.erase(collitionFirst->_targetId);
                    }
                    arrayCollision.erase(it.first);
                }
            }

            components::MasseComponent *MasseComponent =
                this->_componentManager
                    ->getComponent<components::MasseComponent>(it.first);

            sf::Vector2f _prior_S0 = gravityC->_cur_S;
            sf::Vector2f _S_derivs0 =
                (forceComponent ? forceComponent->force : sf::Vector2f(0, 0));
            sf::Vector2f _S_derivs1(0, 0);
            if (MasseComponent && MasseComponent->masse != 0) {
                _S_derivs1 = _prior_S0 / (float)MasseComponent->masse;
            } else {
                _S_derivs1 = _prior_S0 / 1.0f;
            }

            // ExplicitEuler
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