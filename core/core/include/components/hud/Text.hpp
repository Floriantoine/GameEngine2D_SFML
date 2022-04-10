#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

namespace components {

class Text : public fa::Component<Text> {
  public:
    std::string _string;
    sf::Font _font;
    sf::Text _text;

    Text(std::string string, std::string fontPath) : _string(string)
    {
        this->setString(string);
        this->setFont(fontPath);
    }
    static void factory(fa::id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
    bool setFont(std::string fontPath)
    {
        bool output = _font.loadFromFile(fontPath);
        if (output) {
            _text.setFont(_font);
        }
        return output;
    }
    void setString(std::string string)
    {
        _text.setString(string);
        _text.setCharacterSize(24);
        _text.setFillColor(sf::Color::White);
    }
};
} // namespace components