cmake_minimum_required(VERSION 3.5)
project("SFML_Engine2D" LANGUAGES CXX)

set(WARNING_FLAGS
        -Wall
        -Wextra
        -Wpedantic
)

add_executable(my_game_test src/main.cpp)

target_include_directories(my_game_test PUBLIC
  src
  src/parallax
  src/tools
  src/texture
  src/sprite
  src/observer
  include
  include/imgui
)

target_link_libraries(my_game_test
  fa-engine
)

target_compile_options(my_game_test PRIVATE ${WARNING_FLAGS})
target_link_options(my_game_test PRIVATE -rdynamic)
