cmake_minimum_required(VERSION 3.5)

project("R-type's client" LANGUAGES CXX)

set(SRC_DIR src/)


set(WARNING_FLAG
        -Wall
        -Wextra
        -Wpedantic
)

set(SRCS
        Game.cpp
        EventSystem.cpp
        parallax/AParallax.cpp
        parallax/layerBackground.cpp
        parallax/ParallaxSystem.cpp
        parallax/ParallaxLayer.cpp
        parallax/ParallaxObj.cpp
        tools/random.cpp
        tools/jsonTools.cpp
        tools/imgui/implot.cpp
        tools/imgui/implot_items.cpp
        tools/Spooky.cpp
        tools/Chrono.cpp
        scene/SceneManager.cpp
        texture/Texture.cpp
        texture/TextureManager.cpp
        sprite/Sprite.cpp
        sprite/SpriteManager.cpp
        sprite/dynamicSprite.cpp
        particle/ParticleManager.cpp
        component/ComponentManager.cpp
        system/GravitySystem.cpp
        system/FormSystem.cpp
        system/KeyMovement.cpp
        system/ParticlesSystem.cpp
        system/DisplayShape.cpp
        system/CollisionSystem.cpp
        system/CollisionColor.cpp
        factory/PlayerFactory.cpp
)

list(TRANSFORM SRCS PREPEND ${SRC_DIR})

add_executable(r-type_client ${SRCS})

target_include_directories( r-type_client PRIVATE
        ./src
        ./src/parallax
        ./src/tools
        ./src/texture
        ./src/sprite
        ./src/observer
        ./include
        ./include/imgui
)

target_link_libraries(r-type_client PRIVATE
  nlohmann_json::nlohmann_json
  sfml-graphics
    ImGui-SFML::ImGui-SFML
)
