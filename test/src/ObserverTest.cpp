#include "catch2/catch_all.hpp"
#include "observer/ObserverManager.hpp"

TEST_CASE("observer")
{
    ObserverManager _observerM;
    SECTION("init")
    {
        REQUIRE(_observerM.observerCount() == 0);
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

TEST_CASE("Subject")
{
    ObserverManager _observerM;
    SECTION("init")
    {
        REQUIRE(_observerM.subjectCount() == 0);
    }

    SECTION("add sujectb")
    {
        Subject subject;
        _observerM.addSubject(&subject);
        REQUIRE(_observerM.subjectCount() == 1);
    }

    SECTION("remove observer")
    {
        Subject subject;
        _observerM.addSubject(&subject);
        REQUIRE(_observerM.subjectCount() == 1);
        _observerM.deleteSubject(&subject);
        REQUIRE(_observerM.observerCount() == 0);
    }
}

TEST_CASE("ObserverManager")
{
    ObserverManager _observerM;

    SECTION("clear")
    {
        Subject subject;
        auto obs = Observer{
            [&](KeyPressed const &key) {},
        };
        _observerM.addObserver(&obs);
        _observerM.addSubject(&subject);

        REQUIRE(_observerM.observerCount() == 1);
        REQUIRE(_observerM.subjectCount() == 1);

        _observerM.clear();
        REQUIRE(_observerM.observerCount() == 0);
        REQUIRE(_observerM.subjectCount() == 0);
    }
}