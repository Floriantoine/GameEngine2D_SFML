
#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <json/value.h>
#include <memory>

#include "../observer/ObserverManager.hpp"
#include "../tools/jsonTools.hpp"
#include "./IParallax.hpp"
#include "./ParallaxLayer.hpp"
#include "./ParallaxObj.hpp"
#include "./layerBackground.hpp"

namespace parallax {

class ParallaxSystem {
  private:
    std::vector<std::unique_ptr<IParallax>> _layers;
    sf::RenderWindow *_window;
    std::string _filepath;
    std::string _configName;
    int _rate = 16;
    Observer _observer;

  public:
    enum class ParallaxType : int
    {
        LAYER = 0,
        OBJ,
    };
    void clear();
    void update(long elapsed);
    void display();
    void setRenderWindow(sf::RenderWindow *window);
    void addLayer(std::string spritePath, IParallax::ParallaxType,
        nlohmann::json options);
    void initFromFile(std::string filepath, std::string configName);
    void initFromJson(nlohmann::json const &json);
    std::string getConfigFilePath()
    {
        return this->_filepath;
    };
    int getRate()
    {
        return this->_rate;
    };
    void setRate(int rate)
    {
        if (rate > 0 && rate < 1000)
            this->_rate = rate;
    }
    std::string getConfigName()
    {
        return this->_configName;
    };
    void eventClickCallback();

    ParallaxSystem(ObserverManager &observerManager);
    ~ParallaxSystem();
};

} // namespace parallax
