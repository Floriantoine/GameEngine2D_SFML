cmake_minimum_required(VERSION 3.5)

project("SFML_Engine2D" LANGUAGES CXX)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib/)

set(
  WARNING_FLAG
  -Wall
  -Wextra
  -pedantic
  -Wpedantic
)

add_library(fa-engine SHARED
        src/EventSystem.cpp
        src/components/hud/Text.cpp
        src/components/Color.cpp
        src/components/Damage.cpp
        src/components/DiesLeavesScreen.cpp
        src/components/Direction.cpp
        src/components/DirectionSprite.cpp
        src/components/EntitySpawner.cpp
        src/components/ForceComponent.cpp
        src/components/RigideBody.cpp
        src/components/HaveCollisionDamage.cpp
        src/components/HealthComponent.cpp
        src/components/KeyMovement.cpp
        src/components/LoopLife.cpp
        src/components/LifeTime.cpp
        src/components/LinearMovement.cpp
        src/components/MasseComponent.cpp
        src/components/MouseForce.cpp
        src/components/Orbit.cpp
        src/components/ParentRef.cpp
        src/components/ParticleIdentityComponent.cpp
        src/components/PosComponent.cpp
        src/components/PresseSpaceMakeEntity.cpp
        src/components/RectangleShape.cpp
        src/components/Size.cpp
        src/components/SolideBlock.cpp
        src/components/SoundEvent.cpp
        src/components/SpawnMousePos.cpp
        src/components/SpawnPosComponent.cpp
        src/components/Speed.cpp
        src/components/Sprite.cpp
        src/components/TargetEntity.cpp
        src/imgui/ecs/EcsController.cpp
        src/parallax/AParallax.cpp
        src/parallax/layerBackground.cpp
        src/parallax/ParallaxSystem.cpp
        src/parallax/ParallaxLayer.cpp
        src/parallax/ParallaxObj.cpp
        src/tools/random.cpp
        src/tools/jsonTools.cpp
        src/tools/imgui/implot.cpp
        src/tools/imgui/implot_items.cpp
        src/tools/Spooky.cpp
        src/tools/Chrono.cpp
        src/tools/tools.cpp
        src/scene/SceneManager.cpp
        src/texture/Texture.cpp
        src/texture/TextureManager.cpp
        src/sprite/Sprite.cpp
        src/sprite/SpriteManager.cpp
        src/sprite/dynamicSprite.cpp
        src/component/ComponentManager.cpp
        src/system/CollisionColor.cpp
        src/system/CollisionDamage.cpp
        src/system/CollisionSystem.cpp
        src/system/DiesLeavesScreen.cpp
        src/system/DisplayShape.cpp
        src/system/EntityGenerator.cpp
        src/system/EntitySpawner.cpp
        src/system/FormSystem.cpp
        src/system/GravitySystem.cpp
        src/system/HealthSystem.cpp
        src/system/KeyHandler.cpp
        src/system/KeyMovement.cpp
        src/system/MovementSystem.cpp
        src/system/OrbitSystem.cpp
        src/system/ParticlesSystem.cpp
        src/system/SpriteSystem.cpp
        src/factory/EntityFactory.cpp
        src/factory/ParticleFactory.cpp
        src/sound/SoundBuffer.cpp
        src/sound/SoundBufferManager.cpp
        src/entity/Entity.cpp
)

target_compile_options(fa-engine PRIVATE ${WARNING_FLAG})
target_include_directories(fa-engine PUBLIC
        src
        src/parallax
        src/tools
        src/texture
        src/sprite
        src/observer
        include
        include/imgui
)

target_link_libraries(fa-engine
  nlohmann_json::nlohmann_json
  sfml-graphics
  sfml-audio
  ImGui-SFML::ImGui-SFML
)


add_executable(engine src/Game.cpp)

target_link_libraries(engine
  fa-engine
)

target_link_options(engine PRIVATE -rdynamic)
