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
        scene/SceneManager.cpp
        texture/Texture.cpp
        texture/TextureManager.cpp
        sprite/Sprite.cpp
        sprite/SpriteManager.cpp
        sprite/dynamicSprite.cpp
        particle/ParticleSystem.cpp
        component/ComponentManager.cpp
        system/PointParticleGravitySystem.cpp
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
)

target_link_libraries(r-type_client PRIVATE
  nlohmann_json::nlohmann_json
  sfml-graphics
  ImGui-SFML::ImGui-SFML
)
