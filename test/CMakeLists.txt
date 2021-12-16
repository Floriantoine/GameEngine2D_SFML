cmake_minimum_required(VERSION 3.5)

project("R-type's test" LANGUAGES CXX)

set(SRC_DIR src/)

include_directories(
        ../core/src
        ../core/src/parallax
        ../core/src/tools
        ../core/src/texture
        ../core/src/sprite
        ../core/src/observer
        ../core/src/particle
        ../core/src/system
        ../core/include/component
        ../core/include
)

set(WARNING_FLAG
        -Wall
        -Wextra
        -Wpedantic
)

set(SRCS
        main.cpp
        ../../core/src/component/ComponentManager.cpp
        ../../core/src/tools/jsonTools.cpp
)

list(TRANSFORM SRCS PREPEND ${SRC_DIR})

add_executable(r-type_test ${SRCS})

target_link_libraries(r-type_test PRIVATE
  Catch2::Catch2WithMain
  nlohmann_json::nlohmann_json
  sfml-graphics
)
