#ifndef UIINPUT_TEXT_H
#define UIINPUT_TEXT_H

#include "UIElement.h"

class InputField : public UIElement
{
public:
    InputField(UIContainer& uiContainer, float x, float y, float width, float height, sf::Font& font);
    void draw(sf::RenderWindow& window) override;
    void setSelected(bool isSelected);
    bool isSelected() const;
    std::string handleTextEntered(sf::Uint32 unicode);
    sf::FloatRect getGlobalBounds();
    bool operator<(const InputField& other) const;

private:
    sf::Text inputText;
    sf::Text text;
    sf::RectangleShape box;
    bool selected;
};

#endif