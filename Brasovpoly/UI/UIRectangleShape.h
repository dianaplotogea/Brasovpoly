#ifndef UI_RECTANGLE_SHAPE_H
#define UI_RECTANGLE_SHAPE_H

#include "UIElement.h"

class UIRectangleShape : public UIElement // It has to be public so we can put the uiRectangleShapePlayer into the inGameSceneUIElementsThatMustBeDeleted
{
public:
    UIRectangleShape(UIContainer& uiContainer, sf::Vector2f position, sf::Vector2f size, sf::Color color);
    void draw(sf::RenderWindow& window) override;
    void setBorder(float borderThickness, sf::Color borderColor);
    void setPosition(sf::Vector2f position);
    void setColor(sf::Color color);
    sf::Color getColor();
    sf::Vector2f getPosition();
    
private:
    sf::RectangleShape rectangleShape;
};

#endif