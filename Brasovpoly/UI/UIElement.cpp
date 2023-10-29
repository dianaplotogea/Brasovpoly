#include <iostream> 
#include "UIElement.h"
#include "UIContainer.h"  

UIElement::UIElement(UIContainer& uiContainer)
{
    uiContainer.addElement(this);
}

bool UIElement::isVisible()
{
    return visible;
}

void UIElement::setVisible(bool visibleParam)
{
    visible = visibleParam;
}