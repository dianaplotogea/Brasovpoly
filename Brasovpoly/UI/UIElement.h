class UIContainer;

#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <SFML/Graphics.hpp>

class UIElement
{
public:
    UIElement(UIContainer& uiContainer);
    virtual void draw(sf::RenderWindow& window) = 0;
    bool isVisible();
    void setVisible(bool visibleParam);
private:
    bool visible = true;
    
};

#endif