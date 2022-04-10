#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include "tools/random.hpp"
#include <SFML/System/Vector2.hpp>
#include <iostream>

namespace components {

class Size : public fa::Component<Size> {
  public:
    sf::Vector2f _size = sf::Vector2f(1, 1);
    sf::Vector2f _initSize = sf::Vector2f(1, 1);
    sf::Vector2f _rangeMin = sf::Vector2f(0, 0);
    sf::Vector2f _rangeMax = sf::Vector2f(0, 0);
    Size(sf::Vector2f size, sf::Vector2f rangeMin, sf::Vector2f rangeMax)
        : _initSize(size), _rangeMin(rangeMin), _rangeMax(rangeMax)
    {
        _size.x = tools::generate_random_number(
            _initSize.x - rangeMin.x, _initSize.x + rangeMax.x);
        _size.y = tools::generate_random_number(
            _initSize.y - rangeMin.y, _initSize.y + rangeMax.y);
    };
    Size(sf::Vector2f size) : _size(size), _initSize(size)
    {
    }
    Size(nlohmann::json config);
    static void factory(fa::id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components