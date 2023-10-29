#include "PlayerColorSelector.h"
#include <iostream>
#include "../Globals.h"
#include "PlayerSetupMenuHandler.h"



void PlayerColorSelector::createColorSelectorMenu()
{
    playerColorSelectorText = new UIText(globals.getPlayerColorSelectorMenu(), globals.getGlobalFont(), playerColorSelectorTextCharacterSize);
    int numberOfColors = globals.getPlayerColors().size();
    while(numberOfColors !=0)
    {
        if(numberOfColors < numberOfColumns)
        {
            numberOfColumns = numberOfColors;
        }
        int currentColorSelectorButtonPositionX = colorSelectorButtonPositionX;
        for(int i=0;i<numberOfColumns;i++)
        {
            Button* colorSelectorButton = new Button(globals.getPlayerColorSelectorMenu(), currentColorSelectorButtonPositionX, colorSelectorButtonInitialPositionY + colorSelectorButtonPositionY, colorSelectorButtonWidth, colorSelectorButtonHeight, globals.getGlobalFont(), "", globals.getPlayerColors()[numberOfColors-1]);
            colorSelectorButtons.push_back(colorSelectorButton);
            currentColorSelectorButtonPositionX += distanceBetweenElements + colorSelectorButtonWidth;
            numberOfColors--;
        }
        colorSelectorButtonPositionY += distanceBetweenElements + colorSelectorButtonHeight;
    }
    globals.getPlayerColorSelectorMenu().hideAll();

}

void PlayerColorSelector::colorButtonEventHandler(sf::RenderWindow& window)
{
    for(Player* player : globals.getPlayers())
    {
        if(player->getColorButton()->isMouseOver(window))
        {
            globals.getPlayerSetupMenu().hideAll();
            globals.getPlayerColorSelectorMenu().showAll();
            globals.setCurrentState(Globals::GameState::PlayerColorSelection);
            playerColorSelectorText->setString("Select color for Player" + std::to_string(player->getCount()));
            playerColorSelectorText->setPosition(sf::Vector2f(Globals::windowWidth/2 - playerColorSelectorText->getLocalBounds().width/2 , playerColorSelectorTextPositionY));
            currentPlayer = player;
            for(Button* button : colorSelectorButtons)
            {
                if(player->getColor() == button->getColor())
                {
                    button->setBorder(5, sf::Color::White);
                    previousColorSelectorButton = button;
                }
                else
                {
                    button->setBorder(0, sf::Color::White);   
                }
            }
        }
    }
}

void PlayerColorSelector::colorSelectorButtonEventHandler(sf::RenderWindow& window)
{
    for(Button* colorSelectorButton : colorSelectorButtons)
    {
        if(colorSelectorButton->isMouseOver(window))
        {
            currentPlayer->setColor(colorSelectorButton->getColor());
            currentPlayer->getPlayerIndexText()->setColor(colorSelectorButton->getColor());
            PlayerSetupMenuHandler playerSetupMenuHandler; 
            playerSetupMenuHandler.activateStartGameButtonIfAllPlayersAreSet();
            colorSelectorButton->setBorder(5, sf::Color::White);
            if(previousColorSelectorButton != nullptr)
            {
                previousColorSelectorButton->setBorder(0, sf::Color::White);
            }
            previousColorSelectorButton = colorSelectorButton;
        }
    }
}