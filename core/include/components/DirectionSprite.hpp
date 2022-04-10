#pragma once

#include "component/Component.hpp"
#include "components/Direction.hpp"
#include "nlohmann/json.hpp"

namespace components {

class DirectionSprite : public fa::Component<DirectionSprite> {
  public:
    std::unordered_map<std::string, std::string> _textureDirections;
    DirectionSprite(
        std::unordered_map<std::string, std::string> textureDirections)
        : _textureDirections(textureDirections){};
    static void factory(fa::id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components