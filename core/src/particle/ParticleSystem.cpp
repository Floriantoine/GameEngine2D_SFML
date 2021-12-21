#include "particle/ParticleSystem.hpp"
#include "Game.hpp"

void ParticleSystem::display()
{
    Game::Game::getInstance().getWindow()->draw(_vertexArray);
}

void ParticleSystem::loadConfig(std::string string)
{
    this->_componentManager.clear();
    this->_systemManager.clear();
    nlohmann::json json = json::loadJson(string);

    if (json == nlohmann::json::value_t::discarded || json.is_discarded()) {
        std::cout << "Json Config Error" << std::endl;
        return;
    } else {
        if (json["force"] != nullptr)
            this->_componentManager.addComponentRange<rtype::ForceComponent>(
                0, this->_vertexArray.getVertexCount(), json["force"]);
        if (json["pos"] != nullptr)
            this->_componentManager.addComponentRange<rtype::PosComponent>(
                0, this->_vertexArray.getVertexCount(), json["pos"]);
        if (json["size"] != nullptr)
            this->setParticleSize(json["size"]);
        if (json["count"] != nullptr)
            this->setVertexCount(json["count"]);
        if (json["type"] != nullptr) {
            if (json["type"] == "quads")
                this->setPrimitiveType(sf::Quads);
            if (json["type"] == "points")
                this->setPrimitiveType(sf::Points);
        }
        if (json["lifeTime"] != nullptr) {
            this->_componentManager.addComponentRange<rtype::HealthComponent>(
                0, this->_vertexArray.getVertexCount(), json["lifeTime"]);
        }
        if (json["masse"] != nullptr) {
            this->setMasse(json["masse"]);
        }
        if (json["color"] != nullptr) {
            this->setColor(json["color"]);
        }
        if (json["mouseForce"] != nullptr && json["mouseForce"] == true) {
            _systemManager.createSystem<rtype::ParticleMouseForceSystem>(
                Game::Game::getInstance().getObserverManager());
        }
        if (json["mousePos"] != nullptr && json["mousePos"] == true) {
            _systemManager.createSystem<rtype::ParticleMousePosSystem>(
                Game::Game::getInstance().getObserverManager());
        }
        if (json["targetMouse"] != nullptr && json["targetMouse"] == true) {
            _systemManager.createSystem<rtype::ParticleMouseTargetSystem>(
                Game::Game::getInstance().getObserverManager(), &_vertexArray);
        }
        if (json["alphaGradient"] != nullptr && json["alphaGradient"] == true) {
            _systemManager.createSystem<PointParticleAlphaSystem>(
                &_vertexArray);
        }
    }

    this->_componentManager.addComponentRange<rtype::MasseComponent>(
        0, this->_vertexArray.getVertexCount(), this->_initMasse);

    if (this->_vertexArray.getPrimitiveType() == sf::PrimitiveType::Points) {
        this->_componentManager.addComponentRange<components::Gravity>(
            0, this->_vertexArray.getVertexCount());
        _systemManager.createSystem<PointParticleGravitySystem>(&_vertexArray);
    }
    _systemManager.createSystem<rtype::ParticleTimeLifeSystem>();
}

void ParticleSystem::setPrimitiveType(sf::PrimitiveType primType)
{
    if (this->_vertexArray.getPrimitiveType() == primType)
        return;
    int count = _vertexArray.getVertexCount();

    if (primType == sf::PrimitiveType::Quads) {
        _vertexArray.setPrimitiveType(sf::Quads);
        _vertexArray.resize(count * 4);
    }
    // else if (primType == sf::PrimitiveType::Lines)
    //     // _vertexArray = sf::VertexArray(sf::Lines, count * 2);
    else if (primType == sf::PrimitiveType::Points) {
        _vertexArray.setPrimitiveType(sf::Points);
        _vertexArray.resize(count / 4);
    }
    // this->resetAll();
}

void ParticleSystem::reset(int index)
{
}

ParticleSystem::ParticleSystem(ObserverManager &observerManager)
    : _vertexArray(sf::Points, 1000), _componentManager(),
      _observerManager(observerManager), _systemManager(_componentManager)
{
    _observers = Observer{
        [&](KeyPressed const &key) {
            // if (key.key == sf::Keyboard::X) {
            //     if (this->_vertexArray.getPrimitiveType() ==
            //         sf::PrimitiveType::Points)
            //         this->setPrimitiveType(sf::Quads);
            //     else
            //         this->setPrimitiveType(sf::Points);
            // }
            if (key.key == sf::Keyboard::Up)
                this->setParticleSize(this->getSize() + 1);
            if (key.key == sf::Keyboard::Down)
                this->setParticleSize(this->getSize() - 1);
            if (key.key == sf::Keyboard::R)
                this->loadConfig("../core/json/particles/Particles.json");
            if (key.key == sf::Keyboard::D) {
                std::cout << "key input " << std::endl;
                this->loadConfig("../core/json/particles/Default.json");
            }
        },
    };
    _observerManager.addObserver(&_observers);
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::init()
{
    this->resetAll();
}