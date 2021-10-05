
#pragma once

#include "./IParallax.hpp"
#include "nlohmann/json.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace parallax {

class ParallaxSystem;

class AParallax : public IParallax {
    friend class ParallaxSystem;

  private:
    ParallaxSystem *_parallaxManager;

  public:
    AParallax() = delete;
    AParallax(AParallax const &to_copy) noexcept;
    AParallax(AParallax &&to_move) = default;
    AParallax &operator=(AParallax const &to_copy);

    virtual ~AParallax() = default;

    void update(long elapsed) override;
    void display() override;

    void setParallaxManagerRef(ParallaxSystem *parallaxS)
    {
        this->_parallaxManager = parallaxS;
    };

    ParallaxSystem *getParallaxManagerRef() const
    {
        return this->_parallaxManager;
    };

  protected:
    int _amplitude = 0;
    int _initInY = 0;
    int _xStep = 1;
    long _totalLifeTime = 0;
    std::string _spritePath;
    int _layerId;
    bool _inverted;
    sf::Vector2i _pos;
    sf::Vector2u _layerSize;
    sf::RenderWindow *_window;
    sf::Texture _texture;
    sf::Sprite _sprite;

    AParallax(ParallaxSystem *paraS, std::string spritePath, int layerId,
        sf::RenderWindow *win, nlohmann::json options);
};

} // namespace parallax
