#pragma once

#include "ASystem.hpp"

namespace systems {

struct collisStruct
{
    sf::FloatRect _floatRect;
    fa::id_t id;
    std::vector<fa::id_t> *targetsId;
    bool *_haveCollision;
};

class CollisionSystem : public fa::ASystem {
  public:
    long _elapsedTime = 0;
    CollisionSystem() : ASystem(){};
    ~CollisionSystem() = default;

    void update(long elapsedTime) override;
};
} // namespace systems