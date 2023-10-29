#include <iostream>
#include "UIContainer.h"    
#include "UIElement.h"

std::vector<UIElement*>& UIContainer::getElements(){
    return elements;
}
    
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
        element->setVisible(false);
    }
}

void UIContainer::showAll()
{
    for (auto element : elements)
    {
        element->setVisible(true);
    }
}

void UIContainer::clearElements(){
    elements.clear();
}