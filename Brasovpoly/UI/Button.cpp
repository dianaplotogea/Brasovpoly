#include "Button.h"

Button::Button(UIContainer& uiContainer, float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color color, float borderThickness, sf::Color borderColor) : UIElement(uiContainer)
{
    rectangleShape.setPosition(sf::Vector2f(x, y));
    rectangleShape.setSize(sf::Vector2f(width, height));
    rectangleShape.setFillColor(color);
        
    buttonText.setFont(*font);
    buttonText.setString(text);
    buttonText.setCharacterSize(16);
    buttonText.setFillColor(sf::Color::White);
    
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    
    float textX = x + (width - textBounds.width) / 2.0f - textBounds.left;
    float textY = y + (height - textBounds.height) / 2.0f - textBounds.top;
    
    buttonText.setPosition
    (
        x + (width - buttonText.getLocalBounds().width) / 2,
        y + (height - buttonText.getLocalBounds().height) / 2
    );

    setBorder(borderThickness, borderColor);
}

void Button::draw(sf::RenderWindow& window)
{
    if (visible)
    {
        window.draw(rectangleShape);
        window.draw(buttonText);
    }
}


bool Button::isMouseOver(sf::RenderWindow& window)
{
    if (!visible)
    {
        return false; // otherwise the button will be clicked when it isn't even visible
    }
    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;

    float btnPosX = rectangleShape.getPosition().x;
    float btnPosY = rectangleShape.getPosition().y;

    if (mouseX < btnPosX + rectangleShape.getLocalBounds().width && mouseX > btnPosX && mouseY < btnPosY + rectangleShape.getLocalBounds().height && mouseY > btnPosY)
    {
        return true;
    }
    return false;
} 

sf::Color Button::getColor()
{
    return rectangleShape.getFillColor();
}

void Button::setBorder(float borderThickness, sf::Color borderColor)
{
    rectangleShape.setOutlineColor(borderColor);
    rectangleShape.setOutlineThickness(borderThickness);
}