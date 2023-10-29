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
    
    buttonText.setPosition
    (
        x + (width - buttonText.getLocalBounds().width) / 2,
        y + (height - buttonText.getLocalBounds().height) / 2
    );

    setBorder(borderThickness, borderColor);
}

void Button::centerText()
{
    buttonText.setPosition
    (
        rectangleShape.getPosition().x + (rectangleShape.getSize().x - buttonText.getLocalBounds().width) / 2,
        rectangleShape.getPosition().y + (rectangleShape.getSize().y - buttonText.getLocalBounds().height) / 2
    );    
}

void Button::draw(sf::RenderWindow& window)
{
    if (isVisible())
    {
        window.draw(rectangleShape);
        window.draw(buttonText);
    }
}


bool Button::isMouseOver(sf::RenderWindow& window)
{
    if (!isVisible())
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

sf::RectangleShape& Button::getRectangleShape()
{
    return rectangleShape;
}

void Button::setRectangleShape(sf::RectangleShape rectangleShapeParam)
{
    rectangleShape = rectangleShapeParam;
}

UISprite* Button::getUISprite()
{
    return uiSprite;
}

void Button::setUiSprite(UISprite* uiSpriteParam)
{
    uiSprite = uiSpriteParam;
}

sf::Text& Button::getText()
{
    return buttonText;
}

void Button::setText(sf::Text buttonTextParam)
{
    buttonText = buttonTextParam;
}