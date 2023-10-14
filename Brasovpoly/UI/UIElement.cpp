#include <iostream> 
#include "UIElement.h"
#include "UIContainer.h"  


UIElement::UIElement(UIContainer& uiContainer)
{
    uiContainer.addElement(this);
}

void UIElement::hide() { visible = false; }
void UIElement::show() { visible = true; }