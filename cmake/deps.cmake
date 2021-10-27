include(FetchContent)

set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.10.2
    GIT_PROGRESS ON
    GIT_SHALLOW ON
)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/sfml
    GIT_TAG 2.5.1
    GIT_SHALLOW ON
    GIT_PROGRESS ON
)

FetchContent_MakeAvailable(
    json
    sfml
)
