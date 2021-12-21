#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class Gravity : public rtype::Component<Gravity> {
  public:
    std::vector<sf::Vector2f> _cur_S;
    std::vector<sf::Vector2f> _prior_S;
    std::vector<sf::Vector2f> _S_derivs;

  public:
    Gravity()
    {
        _cur_S.resize(2);
        _prior_S.resize(2);
        _S_derivs.resize(2);
    };
};
} // namespace components