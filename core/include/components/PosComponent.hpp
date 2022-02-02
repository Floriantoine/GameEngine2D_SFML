#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class PosComponent : public rtype::Component<PosComponent> {
  public:
    sf::Vector2f _pos{0, 0};

  public:
    PosComponent() = default;
    PosComponent(nlohmann::json config)
    {
        if (config.type() == nlohmann::json::value_t::object) {
            if (config["init"] != nullptr && config["init"].size() == 2) {
                this->_pos = sf::Vector2f(config["init"][0], config["init"][1]);
            }
        } else if (config.type() == nlohmann::json::value_t::array &&
                   config[0] != nullptr && config[1] != nullptr) {
            _pos = sf::Vector2f(config[0], config[1]);
        }
    }
};
} // namespace components