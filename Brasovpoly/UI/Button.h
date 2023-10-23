#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include "UIElement.h"
#include "../Globals.h"

class Button : public UIElement
{
public:
    Button(UIContainer& uiContainer, float x, float y, float width, float height, sf::Font* font = getGlobalFont(), std::string text = "", sf::Color color = sf::Color::Transparent, float borderThickness = 0, sf::Color borderColor = sf::Color::Transparent);
    void centerText();
    void draw(sf::RenderWindow& window) override;
    bool isMouseOver(sf::RenderWindow& window);
    sf::Color getColor();
    void setBorder(float borderThickness, sf::Color borderColor);
    sf::RectangleShape rectangleShape;
    UISprite* uiSprite;
    sf::Text buttonText;
    
    
};

#endif