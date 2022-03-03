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
        components/Color.cpp
        components/Damage.cpp
        components/DiesLeavesScreen.cpp
        components/ForceComponent.cpp
        components/GravityComponent.cpp
        components/HaveCollisionDamage.cpp
        components/HealthComponent.cpp
        components/KeyMovement.cpp
        components/LoopLife.cpp
        components/LifeTime.cpp
        components/LinearMovement.cpp
        components/MasseComponent.cpp
        components/MouseForce.cpp
        components/Orbit.cpp
        components/ParentRef.cpp
        components/ParticleIdentityComponent.cpp
        components/PosComponent.cpp
        components/PresseSpaceMakeEntity.cpp
        components/RectangleShape.cpp
        components/Size.cpp
        components/SolideBlock.cpp
        components/SpawnMousePos.cpp
        components/SpawnPosComponent.cpp
        components/Sprite.cpp
        components/TargetEntity.cpp
        imgui/ecs/EcsController.cpp
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
        component/ComponentManager.cpp
        system/CollisionColor.cpp
        system/CollisionDamage.cpp
        system/CollisionSystem.cpp
        system/DiesLeavesScreen.cpp
        system/DisplayShape.cpp
        system/EntityGenerator.cpp
        system/FormSystem.cpp
        system/GravitySystem.cpp
        system/HealthSystem.cpp
        system/KeyHandler.cpp
        system/KeyMovement.cpp
        system/MovementSystem.cpp
        system/OrbitSystem.cpp
        system/ParticlesSystem.cpp
        system/SpriteSystem.cpp
        factory/PlayerFactory.cpp
        factory/ParticleFactory.cpp
)

list(TRANSFORM SRCS PREPEND ${SRC_DIR})

add_executable(my_game ${SRCS})

target_include_directories(my_game PRIVATE
        ./src
        ./src/parallax
        ./src/tools
        ./src/texture
        ./src/sprite
        ./src/observer
        ./include
        ./include/imgui
)

target_link_libraries(my_game PRIVATE
  nlohmann_json::nlohmann_json
  sfml-graphics
    ImGui-SFML::ImGui-SFML
)
