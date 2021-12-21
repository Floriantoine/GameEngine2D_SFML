include(FetchContent)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.10.2
    GIT_SHALLOW ON
)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/sfml
    GIT_TAG 2.5.1
    GIT_SHALLOW ON
)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.85
    GIT_SHALLOW ON
)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(
    json
    sfml
    Catch2
    imgui
)

set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_DIR ${imgui_SOURCE_DIR})

FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml
    GIT_TAG v2.3
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(
    imgui-sfml
)