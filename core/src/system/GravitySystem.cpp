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
    auto array =
        this->componentManager_->getComponentList<components::Gravity>();
    for (auto it = array.begin(); it != array.end(); ++it) {
        components::Gravity *gravityC =
            static_cast<components::Gravity *>(it->second);
        if (gravityC == nullptr)
            break;
        rtype::ForceComponent *forceComponent =
            this->componentManager_->getComponent<rtype::ForceComponent>(
                it->first);
        rtype::MasseComponent *MasseComponent =
            this->componentManager_->getComponent<rtype::MasseComponent>(
                it->first);

        gravityC->_prior_S = gravityC->_cur_S;
        gravityC->_S_derivs[0] =
            (forceComponent ? forceComponent->force : sf::Vector2f(0, 0));
        gravityC->_S_derivs[1] =
            gravityC->_prior_S[0] /
            (float)(MasseComponent ? MasseComponent->masse : 0);
        ExplicitEuler(gravityC->_cur_S.size(), &gravityC->_cur_S,
            gravityC->_prior_S, gravityC->_S_derivs, delta_t);

        rtype::HealthComponent *compLife =
            this->componentManager_->getComponent<rtype::HealthComponent>(
                it->first);
        if (compLife && compLife->health > 0) {
            (*_vertexArray)[it->first].position = gravityC->_cur_S[1];
        }
    }
}
} // namespace systems