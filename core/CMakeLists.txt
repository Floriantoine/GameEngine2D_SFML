cmake_minimum_required(VERSION 3.5)

project("R-type's client" LANGUAGES CXX)

set(SRC_DIR src/)

include_directories(
        ./src
)

set(WARNING_FLAG
        -Wall
        -Wextra
        -Wpedantic
)

set(SRCS
        Game.cpp
        EventSystem.cpp
        Parallax/AParallax.cpp
        Parallax/layerBackground.cpp
        Parallax/ParallaxSystem.cpp
        Parallax/ParallaxLayer.cpp
        Parallax/ParallaxObj.cpp
        tools/random.cpp
)

list(TRANSFORM SRCS PREPEND ${SRC_DIR})

add_executable(r-type_client ${SRCS})

target_link_libraries(r-type_client PRIVATE
  nlohmann_json::nlohmann_json
  sfml-graphics
)
