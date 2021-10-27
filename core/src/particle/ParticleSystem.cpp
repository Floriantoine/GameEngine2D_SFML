#include "ParticleSystem.hpp"
#include "Game.hpp"

void ParticleSystem::display()
{
    Game::Game::getInstance().getWindow()->draw(_vertexArray);
}

void ParticleSystem::setPrimitiveType(sf::PrimitiveType primType)
{
    if (this->_vertexArray.getPrimitiveType() == primType)
        return;
    int count = _vertexArray.getVertexCount();

    if (primType == sf::PrimitiveType::Quads) {
        _vertexArray.setPrimitiveType(sf::Quads);
        _vertexArray.resize(count * 4);
        this->updateQuads();
    }
    // else if (primType == sf::PrimitiveType::Lines)
    //     // _vertexArray = sf::VertexArray(sf::Lines, count * 2);
    else if (primType == sf::PrimitiveType::Points) {
        _vertexArray.setPrimitiveType(sf::Points);
        _vertexArray.resize(count / 4);
        this->updatePoints();
    }
    // this->resetAll();
}

void ParticleSystem::reset(int index)
{
    int floatX =
        tools::generate_random_number(_mousePos.x - 5, _mousePos.x + 5);
    int floatY =
        tools::generate_random_number(_mousePos.y - 5, _mousePos.y + 5);

    int vertexIndex = index;
    if (_vertexArray.getPrimitiveType() == sf::PrimitiveType::Quads) {
        vertexIndex = vertexIndex * 4;
    }
    _vertexArray[vertexIndex].position = {floatX, floatY};
    _vertexArray[vertexIndex].color.a = 255;
    _vertexArray[vertexIndex].color = sf::Color::Green;

    if (_vertexArray.getPrimitiveType() == sf::PrimitiveType::Quads) {
        _vertexArray[vertexIndex + 1] = _vertexArray[index];
        _vertexArray[vertexIndex + 2] = _vertexArray[index];
        _vertexArray[vertexIndex + 3] = _vertexArray[index];

        _vertexArray[vertexIndex + 1].position = {floatX, floatY + 10};
        _vertexArray[vertexIndex + 2].position = {floatX + 10, floatY + 10};
        _vertexArray[vertexIndex + 3].position = {floatX + 10, floatY};
    }

    _particleInf[index].lifeTime = tools::generate_random_number(2000, 6000);
    _particleInf[index]._clock.restart();
    _particleInf[index].mass = tools::generate_random_number(1, 30);
    _particleInf[index].size = tools::generate_random_number(2, 10);

    int speedX =
        tools::generate_random_number(_mouseVector.x - 3, _mouseVector.x + 3);
    int speedY =
        tools::generate_random_number(_mouseVector.y - 3, _mouseVector.y + 3);
    cur_S[2 * index] =
        _particleInf[index].mass * sf::Vector2f(-speedX, -speedY);
    cur_S[2 * index + 1] = _vertexArray[vertexIndex].position;
}

ParticleSystem::ParticleSystem(ObserverManager &observerManager)
    : _vertexArray(sf::Points, 1000), _particleInf(1000), cur_S(2000),
      prior_S(2000), S_derivs(2000)
{
    auto obs = new Observer{
        [&](MouseMove const &mouse) {
            this->_mouseVector = {_mousePos.x - mouse.x, _mousePos.y - mouse.y};
            _mousePos = sf::Vector2f(mouse.x, mouse.y);
        },
        [&](KeyPressed const &key) {
            if (key.key == sf::Keyboard::X) {
                if (this->_vertexArray.getPrimitiveType() ==
                    sf::PrimitiveType::Points)
                    this->setPrimitiveType(sf::Quads);
                else
                    this->setPrimitiveType(sf::Points);
                // else if (this->_vertexArray.getPrimitiveType() ==
                //  sf::PrimitiveType::Quads)
                // this->_vertexArray.setPrimitiveType(sf::Lines);
            }
        },
    };

    observerManager.addObserver(obs);
    this->resetAll();
}