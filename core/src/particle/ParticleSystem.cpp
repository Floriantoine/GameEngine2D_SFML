#include "ParticleSystem.hpp"
#include "Game.hpp"

void ParticleSystem::display()
{
    Game::Game::getInstance().getWindow()->draw(_vertexArray);
}

ParticleSystem::ParticleSystem(ObserverManager &observerManager)
    : _vertexArray(sf::Points, 1000), _particleInf(1000), cur_S(2000),
      prior_S(2000), S_derivs(2000)
{
    auto obs = new Observer{
        [&](MouseMove const &mouse) {
            _mousePos = sf::Vector2f(mouse.x, mouse.y);
        },
    };

    observerManager.addObserver(obs);
    for (int i = 0; i < _vertexArray.getVertexCount(); i++) {
        this->reset(i);
    }
}