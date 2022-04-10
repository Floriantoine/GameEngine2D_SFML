#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

namespace components {

class Sprite : public fa::Component<Sprite> {
  public:
    int _currentStep = 0;
    sf::Sprite _sprite;
    std::string _textureName;
    bool _isInit = false;
    sf::Clock _clock;
    int _elapseUpdate = 350;

  public:
    static void factory(fa::id_t entityId, nlohmann::json config);
    Sprite(std::string textureName) : _textureName(textureName){};
    ~Sprite() = default;
    void dislayImGuiPanel() override;
};
} // namespace components