#include <iostream>
#include "UIContainer.h"    
#include "UIElement.h"
    
void UIContainer::addElement(UIElement* element)
{
    elements.push_back(element);
}

void UIContainer::draw(sf::RenderWindow& window)
{
    for (auto element : elements)
    {
        element->draw(window);
    }
}

void UIContainer::hideAll() {
    for (auto element : elements)
    {
        element->hide();
    }
}

void UIContainer::showAll()
{
    for (auto element : elements)
    {
        element->show();
    }
}