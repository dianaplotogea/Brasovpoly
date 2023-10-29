#ifndef UITEXT_H
#define UITEXT_H

#include "UIElement.h"
#include "../Globals.h"

class UIText : public UIElement
{
public:
    UIText(UIContainer& uiContainer, sf::Font* font = nullptr, int characterSize = 20, const std::string& text = "", sf::Color color = sf::Color::White);
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getLocalBounds() const;
    void setOrigin(float x, float y);
    void setString(const std::string& text);
    std::string getString();
    void setPosition(const sf::Vector2f& position);
    void setCharacterSize(unsigned int size);
    void setColor(const sf::Color& color);
    sf::FloatRect getLocalBounds();
    sf::Vector2f getPosition();

private:
    sf::Text text;
};

#endif
