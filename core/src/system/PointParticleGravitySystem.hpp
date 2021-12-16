#pragma once

#include "../components/ForceComponent.hpp"
#include "../components/MasseComponent.hpp"
#include "../components/PosComponent.hpp"
#include "./ASystem.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

class PointParticleGravitySystem : public rtype::ASystem {
  private:
    sf::VertexArray *_vertexArray;

    std::vector<sf::Vector2f> cur_S;
    std::vector<sf::Vector2f> prior_S;
    std::vector<sf::Vector2f> S_derivs;
    float delta_t = 0.2;
    int _vertexSize;

    void ExplicitEuler(int N, std::vector<sf::Vector2f> prior_S,
        std::vector<sf::Vector2f> S_derivs, float delta_t)
    {
        for (int i = 0; i < N; i++) {
            cur_S[i] = prior_S[i] + delta_t * S_derivs[i];
        }
    }

  public:
    PointParticleGravitySystem(sf::VertexArray *vertexArray)
        : _vertexArray(vertexArray), cur_S(1), prior_S(1), S_derivs(1),
          _vertexSize(-1), ASystem(){};
    ~PointParticleGravitySystem() = default;

    void init()
    {
        this->_vertexSize = this->_vertexArray->getVertexCount();
        this->cur_S.resize(_vertexSize * 2);
        this->prior_S.resize(_vertexSize * 2);
        this->S_derivs.resize(_vertexSize * 2);

        for (int index = 0; index < _vertexSize; index++) {
            resetParticle(index);
        }
    }

    template <class T>
    void generateProprietyRange(T *value, T initValue, T rangeMin, T rangeMax)
    {
        (*value) = tools::generate_random_number(
            initValue - rangeMin, initValue + rangeMax);
    }

    template <class T>
    void generateVectorProprietyRange(
        T *value, T initValue, T rangeMin, T rangeMax)
    {
        (*value).x = tools::generate_random_number(
            initValue.x - rangeMin.x, initValue.x + rangeMax.x);
        (*value).y = tools::generate_random_number(
            initValue.y - rangeMin.y, initValue.y + rangeMax.y);
    }

    void resetParticle(int index)
    {
        rtype::HealthComponent *compLife =
            this->componentManager_->getComponent<rtype::HealthComponent>(
                index);
        rtype::MasseComponent *MasseComp =
            this->componentManager_->getComponent<rtype::MasseComponent>(index);
        rtype::ForceComponent *ForceComp =
            this->componentManager_->getComponent<rtype::ForceComponent>(index);
        rtype::PosComponent *PosComp =
            this->componentManager_->getComponent<rtype::PosComponent>(index);
        if (MasseComp)
            generateProprietyRange(
                &MasseComp->masse, MasseComp->_initMasse, 1, 1);
        if (compLife)
            generateProprietyRange(&compLife->health, compLife->_initHealth,
                compLife->_rangeMin, compLife->_rangeMax);
        if (ForceComp)
            generateVectorProprietyRange(&ForceComp->force,
                ForceComp->_initForce, ForceComp->_rangeMin,
                ForceComp->_rangeMax);
        if (PosComp) {
            generateVectorProprietyRange(&PosComp->pos, PosComp->_initPos,
                PosComp->_rangeMin, PosComp->_rangeMax);
        }

        (*_vertexArray)[index].position =
            sf::Vector2f(PosComp->pos.x, PosComp->pos.y);
        (*_vertexArray)[index].color = sf::Color::White;
        (*_vertexArray)[index].color.a = 255;

        float masse = (MasseComp ? MasseComp->masse : 0);
        sf::Vector2f force =
            (ForceComp ? ForceComp->force : sf::Vector2f(0, 0));
        cur_S[2 * index] = masse * force;
        cur_S[2 * index + 1] = (*_vertexArray)[index].position;
    }

    void update(long elapsedTime) override
    {
        int count = _vertexArray->getVertexCount();
        if (count != _vertexSize) {
            init();
        }
        prior_S = cur_S;
        for (int i = 0; i < count; i++) {
            rtype::ForceComponent *forceComponent =
                this->componentManager_->getComponent<rtype::ForceComponent>(i);
            sf::Vector2f force =
                (forceComponent ? forceComponent->force : sf::Vector2f(0, 0));
            rtype::MasseComponent *MasseComponent =
                this->componentManager_->getComponent<rtype::MasseComponent>(i);
            float masse = (MasseComponent ? MasseComponent->masse : 0);

            S_derivs[2 * i] = force;
            S_derivs[2 * i + 1] = prior_S[2 * i] / masse;
        }
        ExplicitEuler(cur_S.size(), prior_S, S_derivs, delta_t);

        for (int i = 0; i < count; i++) {
            rtype::HealthComponent *compLife =
                this->componentManager_->getComponent<rtype::HealthComponent>(
                    i);
            (*_vertexArray)[i].position = cur_S[2 * i + 1];
            if (compLife && compLife->health <= 0) {
                resetParticle(i);
            }
        }
    }
};