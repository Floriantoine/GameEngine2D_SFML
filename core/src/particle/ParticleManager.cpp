#include "particle/ParticleManager.hpp"
#include "Game.hpp"

void ParticleManager::display()
{
}

void ParticleManager::setParticleRange(int min, int max)
{
    if (_json["force"] != nullptr)
        this->_componentManager.addComponentRange<components::ForceComponent>(
            min, max, _json["force"]);
    if (_json["pos"] != nullptr) {
        this->_componentManager.addComponentRange<components::PosComponent>(
            min, max, _json["pos"]);
    }
    if (_json["spawnPos"] != nullptr) {
        this->_componentManager.addComponentRange<components::SpawnPos>(
            min, max, _json["spawnPos"]);
    }
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
    if (_json["lifeType"] != nullptr && _json["lifeType"] == "loop") {
        this->_componentManager.addComponentRange<components::LoopLife>(
            min, max);
    }
    if (_json["masse"] != nullptr) {
        this->setMasse(_json["masse"]);
    }
    if (_json["color"] != nullptr) {
        this->setColor(_json["color"]);
    }

    this->_componentManager.addComponentRange<components::ParticleIdentity>(
        min, max);
    this->_componentManager.addComponentRange<components::MasseComponent>(
        min, max, this->_initMasse);
    this->_componentManager.addComponentRange<components::Gravity>(min, max);
    this->_componentManager.addComponentRange<components::SpawnMousePos>(
        min, max);
    // this->_componentManager.addComponentRange<components::SolidBlock>(min,
    // max);

    // Test Form Components
    // auto array =
    //     this->_componentManager.getComponentList<components::PosComponent>();
    // components::PosComponent *PosC = nullptr;
    // for (auto it = array.begin(); it != array.end(); ++it) {
    //     PosC = static_cast<components::PosComponent *>(it->second);
    //     this->_componentManager.addComponent<components::FormComponent>(
    //         it->first, &PosC->_initPos.x);
    // }
}

void ParticleManager::loadConfig(std::string string)
{
    tools::Chrono::start();
    auto array = this->_componentManager
                     .getComponentList<components::ParticleIdentity>();
    for (auto it = array.begin(); it != array.end(); ++it) {
        this->_componentManager.removeAllComponents(it->first);
    }

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
        if (_json["targetMouse"] != nullptr && _json["targetMouse"] == true) {
            _systemManager.createSystem<rtype::ParticleMouseTargetSystem>(
                Game::Game::getInstance().getObserverManager(), &_vertexArray);
        }
        if (_json["count"] != nullptr)
            this->setVertexCount(_json["count"]);
        this->setParticleRange(0, this->_vertexArray.getVertexCount());
    }

    tools::Chrono::end("load Particle config");
}

void ParticleManager::setPrimitiveType(sf::PrimitiveType primType)
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

void ParticleManager::reset(int index)
{
}

ParticleManager::ParticleManager(ObserverManager &observerManager,
    rtype::ComponentManager &componentManager,
    rtype::SystemManager &systemManager)
    : _vertexArray(sf::Points, 1000), _componentManager(componentManager),
      _observerManager(observerManager), _systemManager(systemManager),
      fileDialog()
{
    fileDialog.SetTitle("Load config");
    fileDialog.SetTypeFilters({".json"});
    _observers = Observer{
        [&](KeyPressed const &key) {
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

ParticleManager::~ParticleManager()
{
}

void ParticleManager::update(long elapsedTime)
{
    tools::Chrono::start();
    ImGui::Begin("test");
    if (ImGui::Button("open config file (core->json->particle)"))
        fileDialog.Open();

    auto particlesArray =
        _componentManager.getComponentList<components::ParticleIdentity>();

    int tempo = particlesArray.size();
    ImGui::SliderInt("Count", &tempo, 0, 10000);
    if (tempo != particlesArray.size()) {
        if (tempo > particlesArray.size())
            this->setParticleRange(particlesArray.size(), tempo);
        if (tempo < particlesArray.size())
            this->_componentManager.removeAllComponentsRange(
                tempo, particlesArray.size());
        this->setVertexCount(tempo);
    }
    // this->_jsonEditor.update();

    if (particlesArray.size() > 0) {
        int firstIndex = particlesArray.begin()->first;
        components::SpawnPos *posComp =
            this->_componentManager.getComponent<components::SpawnPos>(
                firstIndex);
        components::ForceComponent *forceComp =
            this->_componentManager.getComponent<components::ForceComponent>(
                firstIndex);
        components::MasseComponent *masseComp =
            this->_componentManager.getComponent<components::MasseComponent>(
                firstIndex);
        components::HealthComponent *LifeComp =
            this->_componentManager.getComponent<components::HealthComponent>(
                firstIndex);
        components::SpawnMousePos *SpawnOnMousePos =
            _componentManager.getComponent<components::SpawnMousePos>(
                firstIndex);
        components::LoopLife *LifeLoop =
            _componentManager.getComponent<components::LoopLife>(firstIndex);

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

        ImGui::Separator();
        if (ImGui::CollapsingHeader("Position")) {
            if (posComp != nullptr) {
                float tempo[6] = {posComp->_initPos.x, posComp->_initPos.y,
                    posComp->_rangeMin.x, posComp->_rangeMin.y,
                    posComp->_rangeMax.x, posComp->_rangeMax.y};
                bool arrayResponse[6] = {
                    false, false, false, false, false, false};
                arrayResponse[0] =
                    ImGui::SliderFloat("Pos X", &tempo[0], 0, 1920);
                arrayResponse[1] =
                    ImGui::SliderFloat("Pos Y", &tempo[1], 0, 1920);

                arrayResponse[2] =
                    ImGui::SliderFloat("Pos Min X", &tempo[2], 0, 1000);
                arrayResponse[3] =
                    ImGui::SliderFloat("Pos Min Y", &tempo[3], 0, 1000);
                arrayResponse[4] =
                    ImGui::SliderFloat("Pos Max X", &tempo[4], 0, 1000);
                arrayResponse[5] =
                    ImGui::SliderFloat("Pos Max Y", &tempo[5], 0, 1000);

                if (arrayResponse[0] || arrayResponse[1] || arrayResponse[2] ||
                    arrayResponse[3] || arrayResponse[4] || arrayResponse[5]) {
                    for (auto it = particlesArray.begin();
                         it != particlesArray.end(); ++it) {
                        components::SpawnPos *spawnPos =
                            _componentManager
                                .getComponent<components::SpawnPos>(it->first);
                        if (arrayResponse[0] || arrayResponse[1]) {
                            spawnPos->_initPos =
                                sf::Vector2f(tempo[0], tempo[1]);
                        }
                        if (arrayResponse[2] || arrayResponse[3]) {
                            spawnPos->_rangeMin =
                                sf::Vector2f(tempo[2], tempo[3]);
                        }
                        if (arrayResponse[4] || arrayResponse[5]) {
                            spawnPos->_rangeMax =
                                sf::Vector2f(tempo[4], tempo[5]);
                        }
                    }
                }
            }
        }

        ImGui::Separator();

        if (ImGui::CollapsingHeader("Force")) {
            if (forceComp != nullptr) {
                float tempo[6] = {forceComp->_initForce.x,
                    forceComp->_initForce.y, forceComp->_rangeMin.x,
                    forceComp->_rangeMin.y, forceComp->_rangeMax.x,
                    forceComp->_rangeMax.y};

                if (ImGui::SliderFloat("Force X", &tempo[0], -20.0f, 20.0f) ||
                    ImGui::SliderFloat("Force Y", &tempo[1], -20.0f, 20.0f)) {
                    _componentManager.apply<components::ForceComponent>(
                        [&](components::ForceComponent *component) {
                            component->_initForce =
                                sf::Vector2f(tempo[0], tempo[1]);
                        });
                }

                if (ImGui::SliderFloat("Force Min X", &tempo[2], 0.0f, 10.0f) ||
                    ImGui::SliderFloat("Force Min Y", &tempo[3], 0.0f, 10.0f)) {
                    _componentManager.apply<components::ForceComponent>(
                        [&](components::ForceComponent *component) {
                            component->_rangeMin =
                                sf::Vector2f(tempo[2], tempo[3]);
                        });
                }
                if (ImGui::SliderFloat("Force Max X", &tempo[4], 0.0f, 10.0f) ||
                    ImGui::SliderFloat("Force Max Y", &tempo[5], 0.0f, 10.0f)) {
                    _componentManager.apply<components::ForceComponent>(
                        [&](components::ForceComponent *component) {
                            component->_rangeMax =
                                sf::Vector2f(tempo[4], tempo[5]);
                        });
                }
                if (ImGui::Button("Force Reset")) {
                    _componentManager.apply<components::ForceComponent>(
                        [&](components::ForceComponent *component) {
                            component->_initForce = sf::Vector2f(0, 0);
                        });
                    _componentManager.apply<components::ForceComponent>(
                        [&](components::ForceComponent *component) {
                            component->_rangeMin = sf::Vector2f(0, 0);
                        });
                    _componentManager.apply<components::ForceComponent>(
                        [&](components::ForceComponent *component) {
                            component->_rangeMax = sf::Vector2f(0, 0);
                        });
                }
            }
        }

        ImGui::Separator();

        if (ImGui::CollapsingHeader("Masse")) {
            if (masseComp != nullptr) {
                int tempo = masseComp->_initMasse;
                ImGui::SliderInt("Masse Slider", &tempo, -20, 20);
                if (ImGui::Button("Reset Masse")) {
                    tempo = 0;
                }
                if (masseComp->_initMasse != tempo) {
                    _componentManager.apply<components::MasseComponent>(
                        [&](components::MasseComponent *component) {
                            component->_initMasse = tempo;
                            component->masse = tempo;
                        });
                }
            }
        }

        ImGui::Separator();
        if (ImGui::CollapsingHeader("Life")) {
            if (LifeComp != nullptr) {
                int life = LifeComp->_initHealth;
                int lifeRangeMin = LifeComp->_rangeMin;
                int lifeRangeMax = LifeComp->_rangeMax;
                ImGui::SliderInt("LifePos", &life, 0, 60000);
                if (LifeComp->_initHealth != life) {
                    _componentManager.apply<components::HealthComponent>(
                        [&](components::HealthComponent *component) {
                            component->_initHealth = life;
                        });
                }
                ImGui::SliderInt("LifeMin", &lifeRangeMin, 0, 6000);
                if (LifeComp->_rangeMin != lifeRangeMin) {
                    _componentManager.apply<components::HealthComponent>(
                        [&](components::HealthComponent *component) {
                            component->_rangeMin = lifeRangeMin;
                        });
                }
                ImGui::SliderInt("LifeMax", &lifeRangeMax, 0, 6000);
                if (LifeComp->_rangeMax != lifeRangeMax) {
                    _componentManager.apply<components::HealthComponent>(
                        [&](components::HealthComponent *component) {
                            component->_rangeMax = lifeRangeMax;
                        });
                }
            }
        }

        bool mouseT = (SpawnOnMousePos != nullptr ? true : false);
        bool tempoMT = mouseT;
        ImGui::Checkbox("Mouse Target ?", &mouseT);
        if (mouseT != tempoMT && mouseT == true) {
            _componentManager.addComponentRange<components::SpawnMousePos>(
                0, this->_vertexArray.getVertexCount());
        } else if (mouseT != tempoMT && mouseT == false) {
            _componentManager.removeComponentRange<components::SpawnMousePos>(
                0, this->_vertexArray.getVertexCount());
        }

        bool lifeLoopT = (LifeLoop != nullptr ? true : false);
        bool tempoLT = lifeLoopT;
        ImGui::Checkbox("ReSpawn ?", &lifeLoopT);
        if (lifeLoopT != tempoLT && lifeLoopT == true) {
            _componentManager.addComponentRange<components::LoopLife>(
                0, this->_vertexArray.getVertexCount());
        } else if (lifeLoopT != tempoLT && lifeLoopT == false) {
            _componentManager.removeComponentRange<components::LoopLife>(
                0, this->_vertexArray.getVertexCount());
        }
    }

    ImGui::End();

    fileDialog.Display();

    if (fileDialog.HasSelected()) {
        this->loadConfig(fileDialog.GetSelected().string());
        fileDialog.ClearSelected();
    }

    // updateCollideState();
    tools::Chrono::start();
    this->_systemManager.update(elapsedTime);
    tools::Chrono::end("Particle - System Update");

    tools::Chrono::end("Particle M - Update");
}

void ParticleManager::init()
{
    this->resetAll();
}