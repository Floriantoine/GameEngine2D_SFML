#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class FormComponent : public fa::Component<FormComponent> {
  public:
    int *_dataLink;

  public:
    FormComponent() = default;
    FormComponent(int *dataLink) : _dataLink(dataLink)
    {
    }
};
} // namespace components