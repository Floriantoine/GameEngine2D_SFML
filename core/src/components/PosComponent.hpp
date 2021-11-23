#pragma once

#include "../component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace rtype {

class PosComponent : public Component<PosComponent> {
  public:
    sf::Vector2i pos{0, 0};
    sf::Vector2i _initPos{0, 0};
    sf::Vector2i _rangeMin{0, 0};
    sf::Vector2i _rangeMax{0, 0};

  public:
    PosComponent() = default;
    PosComponent(nlohmann::json config)
    {
        if (config.type() == nlohmann::json::value_t::object) {
            if (config["init"] != nullptr && config["init"].size() == 2) {
                _initPos = sf::Vector2i(config["init"][0], config["init"][1]);
                pos = _initPos;
            }
            if (config["rangeMin"] != nullptr &&
                config["rangeMin"].size() == 2) {
                _rangeMin =
                    sf::Vector2i(config["rangeMin"][0], config["rangeMin"][1]);
            }
            if (config["rangeMax"] != nullptr &&
                config["rangeMax"].size() == 2) {
                _rangeMax =
                    sf::Vector2i(config["rangeMax"][0], config["rangeMax"][1]);
            }
        } else if (config.type() == nlohmann::json::value_t::array &&
                   config[0] != nullptr && config[1] != nullptr) {
            _initPos = sf::Vector2i(config[0], config[1]);
            pos = _initPos;
        }
    }
};
} // namespace rtype