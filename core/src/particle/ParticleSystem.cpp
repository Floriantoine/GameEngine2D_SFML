#include "particle/ParticleSystem.hpp"
#include "Game.hpp"

void ParticleSystem::display()
{
    Game::Game::getInstance().getWindow()->draw(_vertexArray);
}

void ParticleSystem::setParticleRange(int min, int max)
{
    if (_json["force"] != nullptr)
        this->_componentManager.addComponentRange<components::ForceComponent>(
            min, max, _json["force"]);
    if (_json["pos"] != nullptr)
        this->_componentManager.addComponentRange<components::PosComponent>(
            min, max, _json["pos"]);
    if (_json["size"] != nullptr)
        this->setParticleSize(_json["size"]);
    if (_json["type"] != nullptr) {
        if (_json["type"] == "quads")
            this->setPrimitiveType(sf::Quads);
        if (_json["type"] == "points")
            this->setPrimitiveType(sf::Points);
    }
    if (_json["lifeTime"] != nullptr) {
        this->_componentManager.addComponentRange<components::HealthComponent>(
            min, max, _json["lifeTime"]);
    }
    if (_json["masse"] != nullptr) {
        this->setMasse(_json["masse"]);
    }
    if (_json["color"] != nullptr) {
        this->setColor(_json["color"]);
    }

    this->_componentManager.addComponentRange<components::MasseComponent>(
        min, max, this->_initMasse);
    this->_componentManager.addComponentRange<components::Gravity>(min, max);

    // Test Form Component
    // auto array =
    //     this->_componentManager.getComponentList<components::PosComponent>();
    // components::PosComponent *PosC = nullptr;
    // for (auto it = array.begin(); it != array.end(); ++it) {
    //     PosC = static_cast<components::PosComponent *>(it->second);
    //     this->_componentManager.addComponent<components::FormComponent>(
    //         it->first, &PosC->_initPos.x);
    // }
}

void ParticleSystem::loadConfig(std::string string)
{
    this->_componentManager.clear();
    this->_systemManager.clear();
    this->_json = json::loadJson(string);

    if (_json == nlohmann::json::value_t::discarded || _json.is_discarded()) {
        std::cout << "Json Config Error" << std::endl;
        return;
    } else {
        if (_json["alphaGradient"] != nullptr &&
            _json["alphaGradient"] == true) {
            _systemManager.createSystem<PointParticleAlphaSystem>(
                &_vertexArray);
        }
        if (_json["mouseForce"] != nullptr && _json["mouseForce"] == true) {
            _systemManager.createSystem<rtype::ParticleMouseForceSystem>(
                Game::Game::getInstance().getObserverManager());
        }
        if (_json["mousePos"] != nullptr && _json["mousePos"] == true) {
            _ParticleMousePosSystem =
                _systemManager.createSystem<rtype::ParticleMousePosSystem>(
                    Game::Game::getInstance().getObserverManager());
        }
        if (_json["targetMouse"] != nullptr && _json["targetMouse"] == true) {
            _systemManager.createSystem<rtype::ParticleMouseTargetSystem>(
                Game::Game::getInstance().getObserverManager(), &_vertexArray);
        }
        if (_json["count"] != nullptr)
            this->setVertexCount(_json["count"]);
        this->setParticleRange(0, this->_vertexArray.getVertexCount());
    }

    if (this->_vertexArray.getPrimitiveType() == sf::PrimitiveType::Points) {
        _systemManager.createSystem<systems::GravitySystem>(&_vertexArray);
    }
    // _systemManager.createSystem<systems::FormSystem>();
    _systemManager.createSystem<systems::ResetSystem>();
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
      _observerManager(observerManager), _systemManager(_componentManager),
      fileDialog()
{
    fileDialog.SetTitle("Load config");
    fileDialog.SetTypeFilters({".json"});
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

void ParticleSystem::update(long elapsedTime)
{
    ImGui::Begin("test");
    if (ImGui::Button("open config file (core->json->particle)"))
        fileDialog.Open();
    // this->_jsonEditor.update();

    components::PosComponent *posComp =
        this->_componentManager.getComponent<components::PosComponent>(0);
    components::ForceComponent *forceComp =
        this->_componentManager.getComponent<components::ForceComponent>(0);
    components::HealthComponent *LifeComp =
        this->_componentManager.getComponent<components::HealthComponent>(0);
    // rtype::SizeComponent *SizeComp =
    //     this->_componentManager.getComponent<rtype::SizeComponent>(0);
    // if (SizeComp != nullptr) {
    //     float size = SizeComp->_size;
    //     ImGui::SliderFloat("Size", &size, 1, 100);
    //     if (SizeComp->_size != size) {
    //         _componentManager.apply<rtype::SizeComponent>(
    //             [&](rtype::SizeComponent *component) {
    //                 component->_size = size;
    //             });
    //     }
    // }
    int tempo = _vertexArray.getVertexCount();
    ImGui::SliderInt("Count", &tempo, 0, 100000);
    if (tempo != _vertexArray.getVertexCount()) {
        if (tempo > _vertexArray.getVertexCount())
            this->setParticleRange(this->_vertexArray.getVertexCount(), tempo);
        if (tempo < _vertexArray.getVertexCount())
            this->_componentManager.removeAllComponentsRange(
                tempo, this->_vertexArray.getVertexCount());
        this->setVertexCount(tempo);
    }

    ImGui::Separator();
    ImGui::LabelText("", "Pos");
    if (posComp != nullptr) {
        int tempo[6] = {posComp->_initPos.x, posComp->_initPos.y,
            posComp->_rangeMin.x, posComp->_rangeMin.y, posComp->_rangeMax.x,
            posComp->_rangeMax.y};
        if (ImGui::SliderInt("X", &tempo[0], 0, 1920) ||
            ImGui::SliderInt("Y", &tempo[1], 0, 1920)) {
            _componentManager.apply<components::PosComponent>(
                [&](components::PosComponent *component) {
                    component->_initPos = sf::Vector2i(tempo[0], tempo[1]);
                });
        }

        if (ImGui::SliderInt("Min X", &tempo[2], 0, 1000) ||
            ImGui::SliderInt("Min Y", &tempo[3], 0, 1000)) {
            _componentManager.apply<components::PosComponent>(
                [&](components::PosComponent *component) {
                    component->_rangeMin = sf::Vector2i(tempo[2], tempo[3]);
                });
        }
        if (ImGui::SliderInt("Max X", &tempo[4], 0, 1000) ||
            ImGui::SliderInt("Max Y", &tempo[5], 0, 1000)) {
            _componentManager.apply<components::PosComponent>(
                [&](components::PosComponent *component) {
                    component->_rangeMax = sf::Vector2i(tempo[4], tempo[5]);
                });
        }
    }
    ImGui::Separator();
    ImGui::LabelText("", "Force");
    if (forceComp != nullptr) {
        float tempo[2] = {forceComp->_initForce.x, forceComp->_initForce.y};
        ImGui::SliderFloat2("Force", tempo, -100.0f, 100.0f);
        if (forceComp->_initForce.x != tempo[0] ||
            forceComp->_initForce.y != tempo[1]) {
            _componentManager.apply<components::ForceComponent>(
                [&](components::ForceComponent *component) {
                    component->_initForce = sf::Vector2f(tempo[0], tempo[1]);
                });
        }
    }

    ImGui::Separator();
    ImGui::LabelText("", "Life");

    if (LifeComp != nullptr) {
        int life = LifeComp->_initHealth;
        ImGui::SliderInt("Life", &life, 0, 60000);
        if (LifeComp->_initHealth != life) {
            _componentManager.apply<components::HealthComponent>(
                [&](components::HealthComponent *component) {
                    component->_initHealth = life;
                });
        }
    }

    bool mouseT = (_ParticleMousePosSystem.get() != nullptr ? true : false);
    bool tempoMT = (_ParticleMousePosSystem.get() != nullptr ? true : false);
    ImGui::Checkbox("Mouse Target ?", &mouseT);
    if (mouseT != tempoMT && mouseT == true) {
        _ParticleMousePosSystem =
            _systemManager.createSystem<rtype::ParticleMousePosSystem>(
                Game::Game::getInstance().getObserverManager());
    } else if (mouseT != tempoMT && mouseT == false) {
        _systemManager.removeSystem<rtype::ParticleMousePosSystem>(
            _ParticleMousePosSystem);
        _ParticleMousePosSystem.reset();
    }

    ImGui::End();

    fileDialog.Display();

    if (fileDialog.HasSelected()) {
        this->loadConfig(fileDialog.GetSelected().string());
        fileDialog.ClearSelected();
    }

    // updateCollideState();
    this->_systemManager.update(elapsedTime);
}

void ParticleSystem::init()
{
    this->resetAll();
}