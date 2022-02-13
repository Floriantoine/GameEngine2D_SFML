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

class ParticleManager {
  private:
    struct ParticleInf
    {
        float mass = 10;
        int size = 5;
    };

    std::shared_ptr<rtype::ParticleTimeLifeSystem> _ParticleTimeLifeSystem;
    std::shared_ptr<PointParticleAlphaSystem> _PointParticleAlphaSystem;
    std::shared_ptr<rtype::ParticleMousePosSystem> _ParticleMousePosSystem;

    rtype::ComponentManager &_componentManager;
    rtype::SystemManager &_systemManager;

    sf::VertexArray _vertexArray;
    std::vector<ParticleInf> _particleInf;

    std::vector<sf::Vector2f> S_derivs;
    float delta_t = 0.2;
    std::vector<int> haveCollide;
    std::vector<int> dontHaveCollide;
    int _initSize = 5;
    int _initMasse = 10;
    int _initLifeTime = 2000;
    sf::Color _initColor = sf::Color::Blue;
    Observer _observers;
    ObserverManager &_observerManager;
    ImGui::FileBrowser fileDialog;
    nlohmann::json _json;

  public:
    void init();
    ParticleManager(ObserverManager &observerManager,
        rtype::ComponentManager &componentManager,
        rtype::SystemManager &systemManager);
    ~ParticleManager();
    void loadConfig(std::string string);
    void setParticleRange(int min, int max);

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

    // void updateCollideState()
    // {
    //     haveCollide.clear();
    //     dontHaveCollide.clear();

    //     for (int i = 0; i < _vertexArray.getVertexCount(); i++) {
    //         dontHaveCollide.push_back(i);
    //         if (this->_vertexArray.getPrimitiveType() ==
    //             sf::PrimitiveType::Quads)
    //             i += 3;
    //     }
    //     bool collide;

    //     for (auto it = dontHaveCollide.begin();
    //          it != dontHaveCollide.end() && dontHaveCollide.size() > 0; ++it)
    //          {
    //         collide = false;

    //         if (std::find(haveCollide.begin(), haveCollide.end(), *it) !=
    //             haveCollide.end()) {
    //             /* v contains x */
    //         } else {
    //             for (int x = (it - dontHaveCollide.begin()) + 1;
    //                  x < dontHaveCollide.size() - 1; ++x) {
    //                 if (((int)_vertexArray[*it].position.x ==
    //                         (int)_vertexArray[dontHaveCollide[x]].position.x)
    //                         &&
    //                     ((int)_vertexArray[*it].position.y ==
    //                         (int)_vertexArray[dontHaveCollide[x]].position.y))
    //                         {
    //                     collide = true;
    //                     _vertexArray[dontHaveCollide[x]].color =
    //                     sf::Color::Red;
    //                     haveCollide.push_back(dontHaveCollide[x]);
    //                     dontHaveCollide.erase(dontHaveCollide.begin() + x);
    //                 }
    //             }
    //             if (collide == true) {
    //                 haveCollide.push_back(*it);
    //                 _vertexArray[*it].color = sf::Color::Red;
    //                 --it;
    //                 dontHaveCollide.erase(it + 1);
    //             }
    //         }
    //     }
    // };

    void update(long elapsedTime);

    void display();
};