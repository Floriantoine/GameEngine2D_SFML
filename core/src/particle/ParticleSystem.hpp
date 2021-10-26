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
    void reset(int index)
    {
        _vertexArray[index].position = {
            tools::generate_random_number(_mousePos.x - 5, _mousePos.x + 5),
            tools::generate_random_number(_mousePos.y - 5, _mousePos.y + 5)};
        _vertexArray[index].color.a = 255;
        _vertexArray[index].color = sf::Color::Green;

        _particleInf[index].lifeTime =
            tools::generate_random_number(2000, 6000);
        _particleInf[index]._clock.restart();
        _particleInf[index].mass = tools::generate_random_number(1, 30);

        int speedX = tools::generate_random_number(
            _mouseVector.x - 3, _mouseVector.x + 3);
        int speedY = tools::generate_random_number(
            _mouseVector.y - 3, _mouseVector.y + 3);
        cur_S[2 * index] =
            _particleInf[index].mass * sf::Vector2f(-speedX, -speedY);
        cur_S[2 * index + 1] = _vertexArray[index].position;
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

    void update()
    {
        updateCollideState();
        prior_S = cur_S;
        for (int i = 0; i < _vertexArray.getVertexCount(); i++) {
            _vertexArray[i].color.a -= 255 / _particleInf[i].lifeTime;
            S_derivs[2 * i] = g;
            S_derivs[2 * i + 1] = prior_S[2 * i] / _particleInf[i].mass;
        }
        ExplicitEuler(
            2 * _vertexArray.getVertexCount(), prior_S, S_derivs, delta_t);

        // Update vertexArray pos + check if dead and reset
        for (int i = 0; i < _vertexArray.getVertexCount(); i++) {
            _vertexArray[i].position = cur_S[2 * i + 1];
            if (_particleInf[i]._clock.getElapsedTime().asMilliseconds() >
                _particleInf[i].lifeTime)
                this->reset(i);
        }
    }

    void display();
};
