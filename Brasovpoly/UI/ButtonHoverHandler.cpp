#include "ButtonHoverHandler.h"
#include "Button.h"

sf::Color buttonHoverColor = {128, 128, 128};

void buttonHover(sf::RenderWindow& window)
{
    for(Button* outlineColorHoverButton : outlineColorHoverButtons)
    {
        if(outlineColorHoverButton->isMouseOver(window))
        {
            outlineColorHoverButton->rectangleShape.setOutlineColor(buttonHoverColor);
        }
        else
        {
            outlineColorHoverButton->rectangleShape.setOutlineColor(buttonBorderColor);
        }
    }

    for(Button* spriteColorHoverButton : spriteColorHoverButtons)
    {
        if(spriteColorHoverButton->isMouseOver(window))
        {
            spriteColorHoverButton->uiSprite->setColor(buttonHoverColor);
        }
        else
        {
            spriteColorHoverButton->uiSprite->setColor(sf::Color::White);
        }
    }
}