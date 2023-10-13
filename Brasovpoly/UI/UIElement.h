class UIContainer;

#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <SFML/Graphics.hpp>

class UIElement
{
public:

    UIElement(UIContainer& uiContainer);
    bool visible = true;
    virtual void draw(sf::RenderWindow& window) = 0;
    void hide();
    void show();
    
};

#endif