#include "catch2/catch_all.hpp"
#include "observer/ObserverManager.hpp"

TEST_CASE("observer")
{
    ObserverManager _observerM;
    SECTION("init")
    {
        REQUIRE(_observerM.observerCount() == 0);
        REQUIRE(_observerM.subjectCount() == 0);
    }

    SECTION("add observer")
    {
        auto obs = Observer{
            [&](KeyPressed const &key) {},
        };
        _observerM.addObserver(&obs);
        REQUIRE(_observerM.observerCount() == 1);
    }

    SECTION("remove observer")
    {
        auto obs = Observer{
            [&](KeyPressed const &key) {},
        };
        _observerM.addObserver(&obs);
        REQUIRE(_observerM.observerCount() == 1);
        _observerM.deleteObserver(&obs);
        REQUIRE(_observerM.observerCount() == 0);
    }
}