#pragma once

#include "../tools/jsonTools.hpp"
#include "ParallaxSystem.hpp"
#include "TextureManager.hpp"
#include "nlohmann/json.hpp"

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