#include <catch2/catch_all.hpp>

#include "../tools/jsonTools.hpp"
#include "ComponentManager.hpp"
#include "components/ForceComponent.hpp"
#include "components/HealthComponent.hpp"
#include "nlohmann/json.hpp"

TEST_CASE("JsonLoader")
{
    SECTION("good Json")
    {
        nlohmann::json json = json::loadJson("../test/json/forceComp.json");
        REQUIRE(json != nlohmann::json::value_t::discarded);
        REQUIRE(!json.is_discarded());
    }
    SECTION("bad Json")
    {
        nlohmann::json json = json::loadJson("../test/json/forceCompBad.json");

        REQUIRE(json.is_discarded());
    }
    SECTION("no Json")
    {
        nlohmann::json json = json::loadJson("");
        REQUIRE(json.is_discarded());
    }
}

TEST_CASE("ComponentManager")
{
    nlohmann::json json = json::loadJson("../test/json/forceComp.json");

    if (json != nlohmann::json::value_t::discarded && !json.is_discarded()) {
        rtype::ComponentManager CompM;

        SECTION("init state")
        {
            REQUIRE(CompM.getComponentCount() == 0);
        }
        SECTION("basic add component")
        {
            CompM.addComponent<rtype::ForceComponent>(1, json["force"]);
            REQUIRE(CompM.getComponentCount() == 1);
            CompM.addComponent<rtype::ForceComponent>(2, json["force"]);
            REQUIRE(CompM.getComponentCount() == 2);
        }

        SECTION("basic add range")
        {
            CompM.addComponentRange<rtype::ForceComponent>(
                0, 10, json["force"]);
            REQUIRE(CompM.getComponentCount() == 10);
        }

        SECTION("hasComponent")
        {
            CompM.addComponent<rtype::ForceComponent>(1, json["force"]);
            REQUIRE(CompM.hasComponent<rtype::ForceComponent>(1) == true);
            REQUIRE(CompM.hasComponent<rtype::ForceComponent>(2) == false);
        }

        SECTION("throws")
        {
            CompM.addComponent<rtype::ForceComponent>(1, json["force"]);
            REQUIRE_THROWS(
                CompM.addComponent<rtype::ForceComponent>(1, json["force"]));
            REQUIRE(CompM.getComponentCount() == 1);
        }

        SECTION("remove")
        {
            SECTION("Basique")
            {
                CompM.addComponent<rtype::ForceComponent>(1, json["force"]);
                REQUIRE(CompM.getComponentCount() == 1);
                CompM.removeComponent<rtype::ForceComponent>(1);
                REQUIRE(CompM.getComponentCount() == 0);
            }
            SECTION("All")
            {
                CompM.addComponent<rtype::ForceComponent>(1, json["force"]);
                CompM.addComponent<rtype::HealthComponent>(1, json["lifeTime"]);
                REQUIRE(CompM.getComponentCount() == 2);
                CompM.removeAllComponents(1);
                REQUIRE(CompM.getComponentCount() == 0);
            }
            SECTION("Clear")
            {
                CompM.addComponent<rtype::ForceComponent>(1, json["force"]);
                CompM.addComponent<rtype::HealthComponent>(1, json["lifeTime"]);
                CompM.addComponent<rtype::HealthComponent>(2, json["lifeTime"]);
                CompM.addComponent<rtype::HealthComponent>(3, json["lifeTime"]);
                REQUIRE(CompM.getComponentCount() == 4);
                CompM.clear();
                REQUIRE(CompM.getComponentCount() == 0);
            }
            SECTION("throws")
            {
                REQUIRE_THROWS_WITH(
                    CompM.removeComponent<rtype::ForceComponent>(1),
                    "Entity does not have component");
            }
        }
    }
}