#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class SpawnPos : public fa::Component<SpawnPos> {
  public:
    sf::Vector2f _initPos{0, 0};
    sf::Vector2f _rangeMin{0, 0};
    sf::Vector2f _rangeMax{0, 0};

  public:
    SpawnPos() = default;
    SpawnPos(nlohmann::json config);
    static void factory(id_t entityId, nlohmann::json config);
    SpawnPos(sf::Vector2f initPos, sf::Vector2f rangeMin, sf::Vector2f rangeMax)
        : _initPos(initPos), _rangeMin(rangeMin), _rangeMax(rangeMax){};
    void dislayImGuiPanel() override;
};
} // namespace components