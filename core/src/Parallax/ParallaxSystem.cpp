
#include "./ParallaxSystem.hpp"
#include "../tools/jsonTools.hpp"

namespace parallax {

namespace {
template <typename T_object>
std::unique_ptr<IParallax> createObject(ParallaxSystem *paraS,
    std::string spritePath, int layerId, sf::RenderWindow *win,
    nlohmann::json options)
{
    return std::make_unique<T_object>(paraS, spritePath, layerId, win, options);
}

using entity_ctor = std::unique_ptr<IParallax> (*)(ParallaxSystem *paraS,
    std::string spritePath, int layerId, sf::RenderWindow *win,
    nlohmann::json options);

std::vector<std::pair<IParallax::ParallaxType, entity_ctor>> const
    entity_creators = {
        {IParallax::ParallaxType::BACKGROUND, createObject<LayerBackground>},
        {IParallax::ParallaxType::LAYER, createObject<ParallaxLayer>},
        {IParallax::ParallaxType::OBJ, createObject<ParallaxObj>}};
} // namespace

void ParallaxSystem::clear()
{
    this->_configName = "";
    this->_filepath = "";
    this->_layers.clear();
}

/**
 * init with json config
 * @param filepath, path to background json config
 * @param configName, name Obj in config file
 **/
void ParallaxSystem::initFromFile(std::string filePath, std::string configName)
{
    nlohmann::json json = json::loadJson(filePath);

    if (json == nlohmann::json::value_t::discarded || json.is_discarded()) {
        std::cout << "Json Config Error" << std::endl;
        return;
    } else {
        this->clear();
        this->_filepath = filePath;
        this->_configName = configName;
        for (auto x: json[configName]) {
            std::string path = x["path"];

            auto type = parallax::IParallax::ParallaxType::BACKGROUND;
            if (x["type"] == "LAYER")
                type = parallax::IParallax::ParallaxType::LAYER;
            if (x["type"] == "OBJ")
                type = parallax::IParallax::ParallaxType::OBJ;
            this->addLayer(path, type, x["options"]);
        }
    }
}

void ParallaxSystem::update(long elapsed)
{
    for (size_t i = 0; i < _layers.size(); i++) {
        _layers[i].get()->update(elapsed);
    }
}

void ParallaxSystem::display()
{
    for (size_t i = 0; i < _layers.size(); i++)
        _layers[i].get()->display();
}

void ParallaxSystem::addLayer(std::string spritePath,
    IParallax::ParallaxType type, nlohmann::json options)
{
    auto iter = std::find_if(entity_creators.begin(), entity_creators.end(),
        [&](auto const &entity_creator) {
            return entity_creator.first == type;
        });

    if (iter != entity_creators.end()) {
        _layers.push_back(iter->second(
            this, spritePath, _layers.size() + 1, _window, options));
    }
}

void ParallaxSystem::setRenderWindow(sf::RenderWindow *window)
{
    this->_window = window;
}

ParallaxSystem::ParallaxSystem()
{
}

ParallaxSystem::~ParallaxSystem()
{
}

} // namespace parallax