#include <iostream> 
#include "UIElement.h"
#include "UIContainer.h"  


UIElement::UIElement(UIContainer& uiContainer)
{
    uiContainer.addElement(this);
}