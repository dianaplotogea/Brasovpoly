class UIElement; // Forward declaration

#ifndef UICONTAINER_H
#define UICONTAINER_H

#include <SFML/Graphics.hpp>

class UIContainer
{
public:
    std::vector<UIElement*>& getElements();
    void addElement(UIElement* element);
    void draw(sf::RenderWindow& window);
    void hideAll();
    void showAll();
    void clearElements();

private:
    std::vector<UIElement*> elements;
    
};

#endif