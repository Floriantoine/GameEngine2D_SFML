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
    for (int i = 0; i < count; i++) {
        components::Gravity *gravityC =
            this->componentManager_->getComponent<components::Gravity>(i);
        if (gravityC == nullptr)
            break;
        rtype::ForceComponent *forceComponent =
            this->componentManager_->getComponent<rtype::ForceComponent>(i);
        sf::Vector2f force =
            (forceComponent ? forceComponent->force : sf::Vector2f(0, 0));
        rtype::MasseComponent *MasseComponent =
            this->componentManager_->getComponent<rtype::MasseComponent>(i);
        float masse = (MasseComponent ? MasseComponent->masse : 0);

        gravityC->_prior_S = gravityC->_cur_S;
        gravityC->_S_derivs[0] = force;
        gravityC->_S_derivs[1] = gravityC->_prior_S[0] / masse;
        ExplicitEuler(gravityC->_cur_S.size(), &gravityC->_cur_S,
            gravityC->_prior_S, gravityC->_S_derivs, delta_t);
    }

    for (int i = 0; i < count; i++) {
        rtype::HealthComponent *compLife =
            this->componentManager_->getComponent<rtype::HealthComponent>(i);
        if (compLife && compLife->health <= 0) {
            resetParticle(i);
        } else {
            components::Gravity *gravityC =
                this->componentManager_->getComponent<components::Gravity>(i);
            if (gravityC != nullptr) {
                (*_vertexArray)[i].position = gravityC->_cur_S[1];
            }
        }
    }
}