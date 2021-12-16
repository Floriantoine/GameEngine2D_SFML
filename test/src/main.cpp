#include <catch2/catch_test_macros.hpp>

#include "../tools/jsonTools.hpp"
#include "ComponentManager.hpp"
#include "components/ForceComponent.hpp"
#include "nlohmann/json.hpp"

TEST_CASE("Add Component", "[ComponentManager / addComponent]")
{
    nlohmann::json json = json::loadJson("../test/json/forceComp.json");

    if (json != nlohmann::json::value_t::discarded && !json.is_discarded()) {
        rtype::ComponentManager CompM;
        CompM.addComponent<rtype::ForceComponent>(0, json["force"]);
        REQUIRE(CompM.getComponentListSize() == 1);
        CompM.addComponent<rtype::ForceComponent>(1, json["force"]);
        REQUIRE(CompM.getComponentListSize() == 2);
        // CompM.addComponent<rtype::ForceComponent>(1, json["force"]);
        // REQUIRE(CompM.getComponentListSize() == 2);
    }
}
