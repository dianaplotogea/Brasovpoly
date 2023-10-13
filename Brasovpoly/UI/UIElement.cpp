#include "UIElement.h"
#include "UIContainer.h"  
#include <iostream> 

UIElement::UIElement(UIContainer& uiContainer)
{
    uiContainer.addElement(this);
}

void UIElement::hide() { visible = false; }
void UIElement::show() { visible = true; }