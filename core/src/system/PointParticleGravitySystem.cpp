#include "system/GravitySystem.hpp"

void PointParticleGravitySystem::ExplicitEuler(int N,
    std::vector<sf::Vector2f> *cur_S, std::vector<sf::Vector2f> prior_S,
    std::vector<sf::Vector2f> S_derivs, float delta_t)
{
    for (int i = 0; i < N; i++) {
        (*cur_S)[i] = prior_S[i] + delta_t * S_derivs[i];
    }
}

void PointParticleGravitySystem::init()
{
    this->_vertexSize = this->_vertexArray->getVertexCount();

    for (int index = 0; index < _vertexSize; index++) {
        resetParticle(index);
    }
}

void PointParticleGravitySystem::resetParticle(int index)
{
    components::Gravity *gravityC =
        this->componentManager_->getComponent<components::Gravity>(index);
    if (gravityC == nullptr)
        return;
    rtype::HealthComponent *compLife =
        this->componentManager_->getComponent<rtype::HealthComponent>(index);
    rtype::MasseComponent *MasseComp =
        this->componentManager_->getComponent<rtype::MasseComponent>(index);
    rtype::ForceComponent *ForceComp =
        this->componentManager_->getComponent<rtype::ForceComponent>(index);
    rtype::PosComponent *PosComp =
        this->componentManager_->getComponent<rtype::PosComponent>(index);
    if (MasseComp)
        generateProprietyRange(&MasseComp->masse, MasseComp->_initMasse, 1, 1);
    if (compLife)
        generateProprietyRange(&compLife->health, compLife->_initHealth,
            compLife->_rangeMin, compLife->_rangeMax);
    if (ForceComp)
        generateVectorProprietyRange(&ForceComp->force, ForceComp->_initForce,
            ForceComp->_rangeMin, ForceComp->_rangeMax);
    if (PosComp) {
        generateVectorProprietyRange(&PosComp->pos, PosComp->_initPos,
            PosComp->_rangeMin, PosComp->_rangeMax);
    }

    (*_vertexArray)[index].position =
        sf::Vector2f(PosComp->pos.x, PosComp->pos.y);
    (*_vertexArray)[index].color = sf::Color::White;
    (*_vertexArray)[index].color.a = 255;

    float masse = (MasseComp ? MasseComp->masse : 0);
    sf::Vector2f force = (ForceComp ? ForceComp->force : sf::Vector2f(0, 0));
    gravityC->_cur_S[0] = masse * force;
    gravityC->_cur_S[1] = (*_vertexArray)[index].position;
}

void PointParticleGravitySystem::update(long elapsedTime)
{
    int count = _vertexArray->getVertexCount();
    if (count != _vertexSize) {
        init();
    }
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
        if (compLife && compLife->health <= 0) {
            resetParticle(it->first);
        } else {
            (*_vertexArray)[it->first].position = gravityC->_cur_S[1];
        }
    }
}