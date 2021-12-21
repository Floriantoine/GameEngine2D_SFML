
#include "scene/SceneManager.hpp"

void SceneManager::loadScene(std::string const &filePath)
{
    nlohmann::json json = json::loadJson(filePath);

    if (json == nlohmann::json::value_t::discarded || json.is_discarded()) {
        std::cout << "Json Config Error" << std::endl;
        return;
    } else {
        if (json["parallax"] != NULL)
            _parallaxManager.initFromJson(json["parallax"]);
        if (json["texture"] != NULL) {
            for (auto x: json["texture"]) {
                if (x["path"] != NULL && x["name"] != NULL)
                    _textureManager.createTexture(x["path"], x["name"]);
            }
        }
    }
}

SceneManager::SceneManager(parallax::ParallaxSystem &parallaxManager,
    flowEngine::TextureManager &textureManager)
    : _parallaxManager(parallaxManager), _textureManager(textureManager)
{
}

SceneManager::~SceneManager()
{
}
