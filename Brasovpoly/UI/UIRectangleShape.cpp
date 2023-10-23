#include "UIRectangleShape.h"

UIRectangleShape::UIRectangleShape(UIContainer& uiContainer, sf::Vector2f position, sf::Vector2f size, sf::Color color) : UIElement(uiContainer)
{
    rectangleShape.setPosition(position);
    rectangleShape.setSize(size);
    rectangleShape.setFillColor(color);

}

void UIRectangleShape::setBorder(float borderThickness, sf::Color borderColor)
{
    rectangleShape.setOutlineColor(borderColor);
    rectangleShape.setOutlineThickness(borderThickness);
}

void UIRectangleShape::setPosition(sf::Vector2f position)
{
    rectangleShape.setPosition(position);
}

void UIRectangleShape::draw(sf::RenderWindow& window)
{
    if (visible)
    {
        window.draw(rectangleShape);
        for(sf::RectangleShape border : borders)
        {
            window.draw(border);
        }
    }
}

void UIRectangleShape::setColor(sf::Color color)
{
    rectangleShape.setFillColor(color);
}

sf::Color UIRectangleShape::getColor()
{
    return rectangleShape.getFillColor();
}

sf::Vector2f UIRectangleShape::getPosition()
{
    return rectangleShape.getPosition();
}