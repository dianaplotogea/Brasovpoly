class UIElement; // Forward declaration

#ifndef UICONTAINER_H
#define UICONTAINER_H

#include <SFML/Graphics.hpp>

class UIContainer
{
public:
    std::vector<UIElement*> elements;

    void addElement(UIElement* element);
    void draw(sf::RenderWindow& window);
    void hideAll();
    void showAll();
    
};

#endif