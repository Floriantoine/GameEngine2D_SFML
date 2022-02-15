#include "components/Size.hpp"

namespace components {
Size::Size(nlohmann::json config)
{
    if (config.type() == nlohmann::json::value_t::array &&
        config[0] != nullptr && config[1] != nullptr) {
        _size = sf::Vector2f(config[0], config[1]);
    } else if (config.type() == nlohmann::json::value_t::object) {
        if (config["init"] != nullptr) {
            if (config["init"].type() == nlohmann::json::value_t::array &&
                config["init"].size() == 2) {
                _size = sf::Vector2f(config["init"][0], config["init"][1]);
            } else {
                _size = sf::Vector2f(config["init"], config["init"]);
            }
        }
        if (config["rangeMin"] != nullptr && config["rangeMin"].size() == 2) {
            _rangeMin =
                sf::Vector2f(config["rangeMin"][0], config["rangeMin"][1]);
        }
        if (config["rangeMax"] != nullptr && config["rangeMax"].size() == 2) {
            _rangeMax =
                sf::Vector2f(config["rangeMax"][0], config["rangeMax"][1]);
        }
    } else {
        _size = sf::Vector2f(config, config);
    }
    _initSize = _size;
}
} // namespace components
