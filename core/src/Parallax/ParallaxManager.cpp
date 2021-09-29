
#include "./ParallaxManager.hpp"
#include "../tools/jsonTools.hpp"

namespace parallax {

namespace {
template <typename T_object>
std::unique_ptr<IParallax> createObject(
    std::string spritePath, int layerId, sf::RenderWindow *win, bool inverted)
{
    return std::make_unique<T_object>(spritePath, layerId, win, inverted);
}

using entity_ctor = std::unique_ptr<IParallax> (*)(
    std::string spritePath, int layerId, sf::RenderWindow *win, bool inverted);

std::vector<std::pair<IParallax::ParallaxType, entity_ctor>> const
    entity_creators = {
        {IParallax::ParallaxType::BACKGROUND, createObject<LayerBackground>},
        {IParallax::ParallaxType::LAYER, createObject<ParallaxLayer>},
        {IParallax::ParallaxType::OBJ, createObject<ParallaxObj>}};
} // namespace

void Parallax::clear()
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
void Parallax::initFromFile(std::string filePath, std::string configName)
{
    nlohmann::json json = json::loadJson(filePath);

    if (json == nlohmann::json::value_t::discarded) {
        std::cout << "Json Config Error" << std::endl;
    } else {
        this->clear();
        this->_filepath = filePath;
        this->_configName = configName;
        for (auto x: json[configName]) {
            std::string path = x["path"];
            bool inverted = x["inverted"] == true ? true : false;

            auto type = parallax::IParallax::ParallaxType::BACKGROUND;
            if (x["type"] == "LAYER")
                type = parallax::IParallax::ParallaxType::LAYER;
            if (x["type"] == "OBJ")
                type = parallax::IParallax::ParallaxType::OBJ;
            this->addLayer(path, type, inverted);
        }
    }
}

void Parallax::update()
{
    for (size_t i = 0; i < _layers.size(); i++) {
        _layers[i].get()->update();
    }
}

void Parallax::display()
{
    for (size_t i = 0; i < _layers.size(); i++)
        _layers[i].get()->display();
}

void Parallax::addLayer(
    std::string spritePath, IParallax::ParallaxType type, bool inverted)
{
    auto iter = std::find_if(entity_creators.begin(), entity_creators.end(),
        [&](auto const &entity_creator) {
            return entity_creator.first == type;
        });

    if (iter != entity_creators.end()) {
        _layers.push_back(
            iter->second(spritePath, _layers.size() + 1, _window, inverted));
    }
}

void Parallax::setRenderWindow(sf::RenderWindow *window)
{
    this->_window = window;
}

Parallax::Parallax()
{
}

Parallax::~Parallax()
{
}

} // namespace parallax