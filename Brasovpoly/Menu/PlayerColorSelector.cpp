#include "PlayerColorSelector.h"
#include <iostream>
#include "../Globals.h"
#include "../Player.h"
#include "../UI/Button.h"
#include "../UI/UIText.h"
#include "PlayerSetupMenuHandler.h"

int numberOfColumns = 3;
int distanceBetweenElements = 100;
int colorSelectorButtonWidth = 100;
int colorSelectorButtonHeight = 100;
int colorSelectorButtonPositionX = (windowWidth - numberOfColumns * colorSelectorButtonWidth - (numberOfColumns-1) * distanceBetweenElements)/2;
int colorSelectorButtonInitialPositionY = 225;
int colorSelectorButtonPositionY = 100;

int playerColorSelectorTextPositionY = 200;
int playerColorSelectorTextCharacterSize = 30;

std::vector<Button*> colorSelectorButtons;

UIText* playerColorSelectorText;

Player* currentPlayer;

Button* previousColorSelectorButton = nullptr;

void createColorSelectorMenu()
{
    playerColorSelectorText = new UIText(playerColorSelectorMenu, &font, playerColorSelectorTextCharacterSize);
    int numberOfColors = colors.size();
    while(numberOfColors !=0)
    {
        if(numberOfColors < numberOfColumns)
        {
            numberOfColumns = numberOfColors;
        }
        int currentColorSelectorButtonPositionX = colorSelectorButtonPositionX;
        for(int i=0;i<numberOfColumns;i++)
        {
            Button* colorSelectorButton = new Button(playerColorSelectorMenu, currentColorSelectorButtonPositionX, colorSelectorButtonInitialPositionY + colorSelectorButtonPositionY, colorSelectorButtonWidth, colorSelectorButtonHeight, &font, "", colors[numberOfColors-1]);
            colorSelectorButtons.push_back(colorSelectorButton);
            currentColorSelectorButtonPositionX += distanceBetweenElements + colorSelectorButtonWidth;
            numberOfColors--;
        }
        colorSelectorButtonPositionY += distanceBetweenElements + colorSelectorButtonHeight;
    }
    playerColorSelectorMenu.hideAll();

}

void colorButtonEventHandler(sf::RenderWindow& window)
{
    for(Player* player : players)
    {
        if(player->colorButton->isMouseOver(window))
        {
            playerSetupMenu.hideAll();
            playerColorSelectorMenu.showAll();
            currentState = GameState::PlayerColorSelection;
            playerColorSelectorText->setString("Select color for Player" + std::to_string(player->count));
            playerColorSelectorText->setPosition(sf::Vector2f(windowWidth/2 - playerColorSelectorText->getLocalBounds().width/2 , playerColorSelectorTextPositionY));
            currentPlayer = player;
            for(Button* button : colorSelectorButtons)
            {
                if(player->color == button->getColor())
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

void colorSelectorButtonEventHandler(sf::RenderWindow& window)
{
    for(Button* colorSelectorButton : colorSelectorButtons)
    {
        if(colorSelectorButton->isMouseOver(window))
        {
            currentPlayer->color = colorSelectorButton->getColor();
            currentPlayer->playerIndexText->setColor(colorSelectorButton->getColor()); 
            activateStartGameButtonIfAllPlayersAreSet();
            colorSelectorButton->setBorder(5, sf::Color::White);
            if(previousColorSelectorButton != nullptr)
            {
                previousColorSelectorButton->setBorder(0, sf::Color::White);
            }
            previousColorSelectorButton = colorSelectorButton;
        }
    }
}