#include <catch2/catch_all.hpp>

#include "../tools/jsonTools.hpp"
#include "ComponentManager.hpp"
#include "components/ForceComponent.hpp"
#include "components/HealthComponent.hpp"
#include "components/MasseComponent.hpp"
#include "components/PosComponent.hpp"
#include "components/SpawnPosComponent.hpp"
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
            CompM.addComponent<components::ForceComponent>(1, json["force"]);
            REQUIRE(CompM.getComponentCount() == 1);
            CompM.addComponent<components::ForceComponent>(2, json["force"]);
            REQUIRE(CompM.getComponentCount() == 2);
        }

        SECTION("basic add range")
        {
            CompM.addComponentRange<components::ForceComponent>(
                0, 10, json["force"]);
            REQUIRE(CompM.getComponentCount() == 10);
        }

        SECTION("hasComponent")
        {
            CompM.addComponent<components::ForceComponent>(1, json["force"]);
            REQUIRE(CompM.hasComponent<components::ForceComponent>(1) == true);
            REQUIRE(CompM.hasComponent<components::ForceComponent>(2) == false);
        }

        // SECTION("throws")
        // {
        //     CompM.addComponent<components::ForceComponent>(1, json["force"]);
        //     REQUIRE_THROWS(CompM.addComponent<components::ForceComponent>(
        //         1, json["force"]));
        //     REQUIRE(CompM.getComponentCount() == 1);
        // }

        SECTION("remove")
        {
            SECTION("Basique")
            {
                CompM.addComponent<components::ForceComponent>(
                    1, json["force"]);
                REQUIRE(CompM.getComponentCount() == 1);
                CompM.removeComponent<components::ForceComponent>(1);
                REQUIRE(CompM.getComponentCount() == 0);
            }
            SECTION("All")
            {
                CompM.addComponent<components::ForceComponent>(
                    1, json["force"]);
                CompM.addComponent<components::HealthComponent>(
                    1, json["lifeTime"]);
                REQUIRE(CompM.getComponentCount() == 2);
                CompM.removeAllComponents(1);
                REQUIRE(CompM.getComponentCount() == 0);
            }
            SECTION("Clear")
            {
                CompM.addComponent<components::ForceComponent>(
                    1, json["force"]);
                CompM.addComponent<components::HealthComponent>(
                    1, json["lifeTime"]);
                CompM.addComponent<components::HealthComponent>(
                    2, json["lifeTime"]);
                CompM.addComponent<components::HealthComponent>(
                    3, json["lifeTime"]);
                REQUIRE(CompM.getComponentCount() == 4);
                CompM.clear();
                REQUIRE(CompM.getComponentCount() == 0);
            }
            SECTION("throws")
            {
                REQUIRE_THROWS_WITH(
                    CompM.removeComponent<components::ForceComponent>(1),
                    "Entity does not have component");
            }
        }
    }
}

TEST_CASE("ComponentForce")
{
    nlohmann::json json = json::loadJson("../test/json/forceComp.json");

    if (json != nlohmann::json::value_t::discarded && !json.is_discarded()) {
        rtype::ComponentManager CompM;
        CompM.addComponent<components::ForceComponent>(1, json["force"]);
        auto forceComp = CompM.getComponent<components::ForceComponent>(1);

        SECTION("init")
        {
            REQUIRE(forceComp->force.x == (float)json["force"]["init"][0]);
            REQUIRE(forceComp->force.y == (float)json["force"]["init"][1]);
        }
        SECTION("range")
        {
            REQUIRE(
                forceComp->_rangeMin.y == (float)json["force"]["rangeMin"][1]);
            REQUIRE(
                forceComp->_rangeMin.x == (float)json["force"]["rangeMin"][0]);
            REQUIRE(
                forceComp->_rangeMax.x == (float)json["force"]["rangeMax"][0]);
            REQUIRE(
                forceComp->_rangeMax.y == (float)json["force"]["rangeMax"][1]);
        }
    }
}

TEST_CASE("ComponentLifeTime")
{
    nlohmann::json json = json::loadJson("../test/json/forceComp.json");

    if (json != nlohmann::json::value_t::discarded && !json.is_discarded()) {
        rtype::ComponentManager CompM;
        CompM.addComponent<components::HealthComponent>(1, json["lifeTime"]);
        auto LifeComp = CompM.getComponent<components::HealthComponent>(1);

        SECTION("init")
        {
            REQUIRE(LifeComp->_initHealth == (float)json["lifeTime"]["init"]);
        }
        SECTION("range")
        {
            REQUIRE(LifeComp->_rangeMin == json["lifeTime"]["rangeMin"]);
            REQUIRE(LifeComp->_rangeMax == json["lifeTime"]["rangeMax"]);
        }
    }
}

TEST_CASE("ComponentMasse")
{
    nlohmann::json json = json::loadJson("../test/json/forceComp.json");

    if (json != nlohmann::json::value_t::discarded && !json.is_discarded()) {
        rtype::ComponentManager CompM;
        CompM.addComponent<components::MasseComponent>(
            1, json["masse"]["init"]);
        auto MasseComp = CompM.getComponent<components::MasseComponent>(1);

        SECTION("init")
        {
            REQUIRE(MasseComp->_initMasse == (float)json["masse"]["init"]);
        }
    }
}

TEST_CASE("ComponentPos")
{
    nlohmann::json json = json::loadJson("../test/json/forceComp.json");

    if (json != nlohmann::json::value_t::discarded && !json.is_discarded()) {
        rtype::ComponentManager CompM;
        CompM.addComponent<components::SpawnPos>(1, json["pos"]);
        auto posComp = CompM.getComponent<components::SpawnPos>(1);

        SECTION("init")
        {
            REQUIRE(posComp->_initPos.x == (float)json["pos"]["init"][0]);
            REQUIRE(posComp->_initPos.y == (float)json["pos"]["init"][1]);
        }
        SECTION("range")
        {
            REQUIRE(posComp->_rangeMin.y == (float)json["pos"]["rangeMin"][1]);
            REQUIRE(posComp->_rangeMin.x == (float)json["pos"]["rangeMin"][0]);
            REQUIRE(posComp->_rangeMax.x == (float)json["pos"]["rangeMax"][0]);
            REQUIRE(posComp->_rangeMax.y == (float)json["pos"]["rangeMax"][1]);
        }
    }
}