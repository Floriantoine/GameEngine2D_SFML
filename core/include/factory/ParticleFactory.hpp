#pragma once

#include "Systems.hpp"
#include "component/ComponentManager.hpp"
#include "observer/ObserverManager.hpp"
#include "tools/random.hpp"
#include <SFML/Graphics/VertexArray.hpp>

#include "../tools/Chrono.hpp"
#include "../tools/jsonTools.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#include "imgui/imfilebrowser.h"
#include "system/SystemManager.hpp"
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <vector>

class ParticleFactory {
  private:
    rtype::ComponentManager &_componentManager;
    rtype::SystemManager &_systemManager;

    sf::VertexArray _vertexArray;

    Observer _observers;
    ObserverManager &_observerManager;
    ImGui::FileBrowser fileDialog;
    nlohmann::json _json;

  public:
    ParticleFactory(ObserverManager &observerManager,
        rtype::ComponentManager &componentManager,
        rtype::SystemManager &systemManager);
    ~ParticleFactory();
    void loadConfig(std::string string);
    void setParticleRange(int min, int max);

    void setVertexCount(int count)
    {
        if (this->_vertexArray.getPrimitiveType() == sf::PrimitiveType::Quads)
            count *= 4;
        this->_vertexArray.resize(count);
        // this->resetAll();
    };

    void update(long elapsedTime);

    void display();
};
