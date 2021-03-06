#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class PresseSpaceMakeEntity : public fa::Component<PresseSpaceMakeEntity> {
  public:
    std::string _configPath;

  public:
    PresseSpaceMakeEntity(std::string configPath);
    ~PresseSpaceMakeEntity() = default;
    static void factory(fa::id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components