#include "system/GravitySystem.hpp"

namespace systems {

void GravitySystem::ExplicitEuler(int N, std::vector<sf::Vector2f> *cur_S,
    std::vector<sf::Vector2f> prior_S, std::vector<sf::Vector2f> S_derivs,
    float delta_t)
{
    for (int i = 0; i < N; i++) {
        (*cur_S)[i] = prior_S[i] + delta_t * S_derivs[i];
    }
}

void GravitySystem::update(long elapsedTime)
{
    this->_elapsedtime += elapsedTime;
    if (this->_elapsedtime >= 16) {
        auto array =
            this->componentManager_->getComponentList<components::Gravity>();
        for (auto it = array.begin(); it != array.end(); ++it) {
            components::Gravity *gravityC =
                static_cast<components::Gravity *>(it->second);
            if (gravityC == nullptr)
                break;
            components::ForceComponent *forceComponent =
                this->componentManager_
                    ->getComponent<components::ForceComponent>(it->first);
            components::MasseComponent *MasseComponent =
                this->componentManager_
                    ->getComponent<components::MasseComponent>(it->first);
            components::PosComponent *PosC =
                this->componentManager_->getComponent<components::PosComponent>(
                    it->first);

            if (PosC) {
                gravityC->_cur_S[1] = PosC->_pos;
            }
            gravityC->_prior_S = gravityC->_cur_S;
            gravityC->_S_derivs[0] =
                (forceComponent ? forceComponent->force : sf::Vector2f(0, 0));
            gravityC->_S_derivs[1] =
                gravityC->_prior_S[0] /
                (float)(MasseComponent ? MasseComponent->masse : 0);
            ExplicitEuler(gravityC->_cur_S.size(), &gravityC->_cur_S,
                gravityC->_prior_S, gravityC->_S_derivs,
                delta_t * (_elapsedtime / 16.0f));

            if (PosC)
                PosC->_pos = gravityC->_cur_S[1];
        }
        this->_elapsedtime = 0;
    }
}
} // namespace systems