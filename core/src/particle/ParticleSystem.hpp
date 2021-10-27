#pragma once

#include "../observer/ObserverManager.hpp"
#include "tools/random.hpp"
#include <SFML/Graphics/VertexArray.hpp>

#include <SFML/System/Clock.hpp>
#include <iostream>
#include <vector>

class ParticleSystem {
  private:
    struct ParticleInf
    {
        sf::Clock _clock;
        float lifeTime = 2000;
        float mass = 10;
    };

    sf::VertexArray _vertexArray;
    std::vector<ParticleInf> _particleInf;

    std::vector<sf::Vector2f> cur_S;
    std::vector<sf::Vector2f> prior_S;
    std::vector<sf::Vector2f> S_derivs;
    sf::Vector2f g = {0, 9.81};
    float delta_t = 0.2;
    std::vector<int> haveCollide;
    std::vector<int> dontHaveCollide;
    sf::Vector2f _mousePos = {200, 200};
    sf::Vector2f _mouseVector = {7, 7};

  public:
    ParticleSystem(ObserverManager &observerManager);
    ~ParticleSystem() = default;
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

    void ExplicitEuler(int N, std::vector<sf::Vector2f> prior_S,
        std::vector<sf::Vector2f> S_derivs, float delta_t)
    {
        for (int i = 0; i < N; i++) {
            cur_S[i] = prior_S[i] + delta_t * S_derivs[i];
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
                    _vertexArray[*it].color = sf::Color::Blue;
                    --it;
                    dontHaveCollide.erase(it + 1);
                }
            }
        }
    };

    void updateQuads()
    {
        for (int i = 0; i < _vertexArray.getVertexCount() / 4; i++) {
            int real = i * 4;
            _vertexArray[real].position = cur_S[2 * i + 1];
            _vertexArray[real + 1].position = {
                cur_S[2 * i + 1].x, cur_S[2 * i + 1].y + 5};
            _vertexArray[real + 2].position = {
                cur_S[2 * i + 1].x + 5, cur_S[2 * i + 1].y + 5};
            _vertexArray[real + 3].position = {
                cur_S[2 * i + 1].x + 5, cur_S[2 * i + 1].y};
            if (_particleInf[i]._clock.getElapsedTime().asMilliseconds() >
                _particleInf[i].lifeTime)
                this->reset(i);
        }
    }

    void updatePoints()
    {
        for (int i = 0; i < _vertexArray.getVertexCount(); i++) {
            _vertexArray[i].position = cur_S[2 * i + 1];
            if (_particleInf[i]._clock.getElapsedTime().asMilliseconds() >
                _particleInf[i].lifeTime)
                this->reset(i);
        }
    }

    void update()
    {
        updateCollideState();

        int count = _vertexArray.getVertexCount();
        if (this->_vertexArray.getPrimitiveType() == sf::PrimitiveType::Quads)
            count = count / 4;
        prior_S = cur_S;
        for (int i = 0; i < count; i++) {
            // _vertexArray[i].color.a -= 255 / _particleInf[i].lifeTime;
            S_derivs[2 * i] = g;
            S_derivs[2 * i + 1] = prior_S[2 * i] / _particleInf[i].mass;
        }
        ExplicitEuler(cur_S.size(), prior_S, S_derivs, delta_t);

        if (this->_vertexArray.getPrimitiveType() == sf::PrimitiveType::Quads)
            this->updateQuads();
        if (this->_vertexArray.getPrimitiveType() == sf::PrimitiveType::Points)
            this->updatePoints();
    }

    void display();
};
