#pragma once

#include "TextureManager.hpp"
#include "nlohmann/json.hpp"
#include "parallax/ParallaxSystem.hpp"
#include "tools/jsonTools.hpp"

class SceneManager {
  private:
    parallax::ParallaxSystem &_parallaxManager;
    flowEngine::TextureManager &_textureManager;

  public:
    SceneManager(parallax::ParallaxSystem &paraManager,
        flowEngine::TextureManager &textureManager);
    ~SceneManager();

    void loadScene(std::string const &path);
};