#pragma once

#include "../observer/ObserverManager.hpp"
#include "component/ComponentManager.hpp"
#include "system/ParticleMouseForceSystem.hpp"
#include "system/ParticleMousePosSystem.hpp"
#include "system/ParticleMouseTargetSystem.hpp"
#include "system/ParticleTimeLifeSystem.hpp"
#include "system/PointParticleAlphaSystem.hpp"
#include "system/PointParticleBasicSystem.hpp"
#include "system/PointParticleGravitySystem.hpp"
#include "tools/random.hpp"
#include <SFML/Graphics/VertexArray.hpp>

#include "../tools/jsonTools.hpp"
#include "system/SystemManager.hpp"
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <vector>

class ParticleSystem {
  private:
    struct ParticleInf
    {
        float mass = 10;
        int size = 5;
    };

    rtype::ComponentManager _componentManager;
    rtype::SystemManager _systemManager;

    sf::VertexArray _vertexArray;
    std::vector<ParticleInf> _particleInf;

    std::vector<sf::Vector2f> cur_S;
    std::vector<sf::Vector2f> prior_S;
    std::vector<sf::Vector2f> S_derivs;
    float delta_t = 0.2;
    std::vector<int> haveCollide;
    std::vector<int> dontHaveCollide;
    sf::Vector2i _mousePos = {200, 200};
    sf::Vector2f _mouseVector = {7, 7};
    sf::Vector2f _force = {0, 9.81};
    int _initSize = 5;
    int _initMasse = 10;
    int _initLifeTime = 2000;
    sf::Color _initColor = sf::Color::Blue;
    Observer _observers;
    ObserverManager &_observerManager;

  public:
    void init();
    ParticleSystem(ObserverManager &observerManager);
    ~ParticleSystem();
    void loadConfig(std::string string);
    void setColor(std::string color)
    {
        if (color == "red")
            this->_initColor = sf::Color::Red;
        if (color == "blue")
            this->_initColor = sf::Color::Blue;
        if (color == "green")
            this->_initColor = sf::Color::Green;
    }
    void setLifeTime(int lifeTime)
    {
        this->_initLifeTime = lifeTime;
    }
    void setVertexCount(int count)
    {
        this->cur_S.resize(count * 2);
        this->prior_S.resize(count * 2);
        this->S_derivs.resize(count * 2);
        this->_particleInf.resize(count);
        if (this->_vertexArray.getPrimitiveType() == sf::PrimitiveType::Quads)
            count *= 4;
        this->_vertexArray.resize(count);
        // this->resetAll();
    };
    void setParticleSize(int size)
    {
        if (size >= 0)
            this->_initSize = size;
    }
    int getSize() const
    {
        return this->_initSize;
    }
    void setMasse(int masse)
    {
        this->_initMasse = masse;
    }
    void setPrimitiveType(sf::PrimitiveType primType);
    void reset(int index);
    void resetAll()
    {
        int count = _vertexArray.getVertexCount();
        if (this->_vertexArray.getPrimitiveType() == sf::PrimitiveType::Quads) {
            count = count / 4;
        }
        for (int index = 0; index < count; index++) {
            reset(index);
        }
    }

    void updateCollideState()
    {
        haveCollide.clear();
        dontHaveCollide.clear();

        for (int i = 0; i < _vertexArray.getVertexCount(); i++) {
            dontHaveCollide.push_back(i);
            if (this->_vertexArray.getPrimitiveType() ==
                sf::PrimitiveType::Quads)
                i += 3;
        }
        bool collide;

        for (auto it = dontHaveCollide.begin();
             it != dontHaveCollide.end() && dontHaveCollide.size() > 0; ++it) {
            collide = false;

            if (std::find(haveCollide.begin(), haveCollide.end(), *it) !=
                haveCollide.end()) {
                /* v contains x */
            } else {
                for (int x = (it - dontHaveCollide.begin()) + 1;
                     x < dontHaveCollide.size() - 1; ++x) {
                    if (((int)_vertexArray[*it].position.x ==
                            (int)_vertexArray[dontHaveCollide[x]].position.x) &&
                        ((int)_vertexArray[*it].position.y ==
                            (int)_vertexArray[dontHaveCollide[x]].position.y)) {
                        collide = true;
                        _vertexArray[dontHaveCollide[x]].color = sf::Color::Red;
                        haveCollide.push_back(dontHaveCollide[x]);
                        dontHaveCollide.erase(dontHaveCollide.begin() + x);
                    }
                }
                if (collide == true) {
                    haveCollide.push_back(*it);
                    _vertexArray[*it].color = sf::Color::Red;
                    --it;
                    dontHaveCollide.erase(it + 1);
                }
            }
        }
    };

    void updateQuads()
    {
        for (int i = 0; i < _vertexArray.getVertexCount() / 4; i++) {
            int quadsSize = _particleInf[i].size;
            int real = i * 4;
            _vertexArray[real].position = cur_S[2 * i + 1];
            _vertexArray[real + 1].position = {
                cur_S[2 * i + 1].x, cur_S[2 * i + 1].y + quadsSize};
            _vertexArray[real + 2].position = {
                cur_S[2 * i + 1].x + quadsSize, cur_S[2 * i + 1].y + quadsSize};
            _vertexArray[real + 3].position = {
                cur_S[2 * i + 1].x + quadsSize, cur_S[2 * i + 1].y};
            auto compLife =
                this->_componentManager.getComponent<rtype::HealthComponent>(i);
            if (compLife && compLife->health <= 0) {
                this->reset(i);
            } else if (compLife) {
                _vertexArray[i].color.a -= 255 / compLife->_initHealth;
            }
        }
    }

    void ExplicitEuler(int N, std::vector<sf::Vector2f> prior_S,
        std::vector<sf::Vector2f> S_derivs, float delta_t)
    {
        for (int i = 0; i < N; i++) {
            cur_S[i] = prior_S[i] + delta_t * S_derivs[i];
        }
    }

    void update(long elapsedTime)
    {
        // updateCollideState();
        this->_systemManager.update(elapsedTime);

        int count = _vertexArray.getVertexCount();
        if (this->_vertexArray.getPrimitiveType() == sf::PrimitiveType::Quads)
            count = count / 4;
        prior_S = cur_S;
        for (int i = 0; i < count; i++) {
            S_derivs[2 * i] = this->_force;
            S_derivs[2 * i + 1] = prior_S[2 * i] / _particleInf[i].mass;
        }
        ExplicitEuler(cur_S.size(), prior_S, S_derivs, delta_t);

        if (this->_vertexArray.getPrimitiveType() == sf::PrimitiveType::Quads)
            this->updateQuads();
    }

    void display();
};
