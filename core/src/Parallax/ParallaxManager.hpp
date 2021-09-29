
#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <json/value.h>
#include <memory>

#include "./IParallax.hpp"
#include "./ParallaxLayer.hpp"
#include "./ParallaxObj.hpp"
#include "./layerBackground.hpp"
#include "nlohmann/json.hpp"

// #include <resource.hpp>

namespace parallax {

class Parallax {
  private:
    std::vector<std::unique_ptr<IParallax>> _layers;
    sf::RenderWindow *_window;
    std::string _filepath;
    std::string _configName;

  public:
    enum class ParallaxType : int
    {
        LAYER = 0,
        OBJ,
    };
    void clear();
    void update();
    void display();
    void setRenderWindow(sf::RenderWindow *window);
    void addLayer(
        std::string spritePath, IParallax::ParallaxType, bool inverted = false);
    void initFromFile(std::string filepath, std::string configName);
    std::string getConfigFilePath()
    {
        return this->_filepath;
    };
    std::string getConfigName()
    {
        return this->_configName;
    };
    Parallax();
    ~Parallax();
};

} // namespace parallax
