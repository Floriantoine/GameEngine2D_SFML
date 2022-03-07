#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <iostream>

namespace components {

class Speed : public fa::Component<Speed> {
  public:
    float _speed = 0;
    float _initSpeed = 0;
    float _rangeMin = 0;
    float _rangeMax = 0;

    Speed(float speed, float rangeMin, float rangeMax)
        : _speed(speed), _initSpeed(speed), _rangeMin(rangeMin),
          _rangeMax(rangeMax)
    {
    }
    Speed(float speed) : _speed(speed), _initSpeed(speed)
    {
    }
    Speed(nlohmann::json config);
    static void factory(id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components