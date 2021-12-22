#pragma once

#include "ASystem.hpp"
#include "Components.hpp"
#include "tools/random.hpp"
#include <vector>

namespace systems {

class ResetSystem : public rtype::ASystem {
  private:
  public:
    ResetSystem() : ASystem(){};
    ~ResetSystem() = default;

    template <class T>
    void generateProprietyRange(T *value, T initValue, T rangeMin, T rangeMax)
    {
        (*value) = tools::generate_random_number(
            initValue - rangeMin, initValue + rangeMax);
    }

    template <class T>
    void generateVectorProprietyRange(
        T *value, T initValue, T rangeMin, T rangeMax)
    {
        (*value).x = tools::generate_random_number(
            initValue.x - rangeMin.x, initValue.x + rangeMax.x);
        (*value).y = tools::generate_random_number(
            initValue.y - rangeMin.y, initValue.y + rangeMax.y);
    }

    void reset(int index);

    void update(long elapsedTime) override;
};
} // namespace systems