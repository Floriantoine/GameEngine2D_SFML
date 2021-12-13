#pragma once

#include "../components/ForceComponent.hpp"
#include "../components/HealthComponent.hpp"
#include "../components/MasseComponent.hpp"
#include "../components/PosComponent.hpp"
#include "./ASystem.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

class PointParticleBasicSystem : public rtype::ASystem {
  private:
    sf::VertexArray *_vertexArray;

    float delta_t = 0.2;
    int _vertexSize;

  public:
    PointParticleBasicSystem(sf::VertexArray *vertexArray)
        : _vertexArray(vertexArray), _vertexSize(-1), ASystem(){};
    ~PointParticleBasicSystem() = default;

    void init()
    {
        this->_vertexSize = this->_vertexArray->getVertexCount();
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
        rtype::ForceComponent *ForceComp =
            this->componentManager_->getComponent<rtype::ForceComponent>(index);
        rtype::PosComponent *PosComp =
            this->componentManager_->getComponent<rtype::PosComponent>(index);
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
    }

    void update(long elapsedTime) override
    {
        int count = _vertexArray->getVertexCount();
        if (count != _vertexSize) {
            init();
        }
        for (int i = 0; i < count; i++) {
            rtype::HealthComponent *compLife =
                this->componentManager_->getComponent<rtype::HealthComponent>(
                    i);
            rtype::ForceComponent *forceComponent =
                this->componentManager_->getComponent<rtype::ForceComponent>(i);
            sf::Vector2f force =
                (forceComponent ? forceComponent->force : sf::Vector2f(0, 0));
            if (compLife && compLife->health <= 0) {
                resetParticle(i);
            } else {
                (*_vertexArray)[i].position += force * (float)elapsedTime;
            }
        }
    }
};