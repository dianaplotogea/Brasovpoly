#include "ButtonHoverHandler.h"
#include "Button.h"



void ButtonHoverHandler::buttonHover(sf::RenderWindow& window)
{
    for(Button* outlineColorHoverButton : globals.getOutlineColorHoverButtons())
    {
        if(outlineColorHoverButton->isMouseOver(window))
        {
            outlineColorHoverButton->getRectangleShape().setOutlineColor(buttonHoverColor);
        }
        else
        {
            outlineColorHoverButton->getRectangleShape().setOutlineColor(globals.getButtonBorderColor());
        }
    }

    for(Button* spriteColorHoverButton : globals.getSpriteColorHoverButtons())
    {
        if(spriteColorHoverButton->isMouseOver(window))
        {
            spriteColorHoverButton->getUISprite()->setColor(buttonHoverColor);
        }
        else
        {
            spriteColorHoverButton->getUISprite()->setColor(sf::Color::White);
        }
    }
}