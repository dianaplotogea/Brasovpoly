#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "UI/Button.h"
#include "UI/UIText.h"
#include "PlayerCountSelectionMenuHandler.h"
#include "PlayerSetupMenuHandler.h"
#include "Globals.h"

int maximumNumberOfPlayers = 6;
int playerCountSelectionButtonInitialPositionY = 150;
int playerCountSelectionButtonDistanceBetweenButtonsY = 100;

std::vector<Button*> playerCountSelectionButtons;

void createPlayerCountSelectionMenu()
{
    std::cout<<"Creating menu" << std::endl;
    UIText* playerCountSelectionText = new UIText(playerCountSelectionMenu, &font, 24, "Select the number of players:");
    playerCountSelectionText->setPosition(sf::Vector2f(windowWidth/2, 50));
    sf::FloatRect playerCountSelectionTextRect = playerCountSelectionText->getLocalBounds();
    playerCountSelectionText->setOrigin(playerCountSelectionTextRect.left + playerCountSelectionTextRect.width/2.0f, playerCountSelectionTextRect.top  + playerCountSelectionTextRect.height/2.0f);

    for(int i=2;i<maximumNumberOfPlayers+1;i++)
    {
        Button* numberOfPlayersSelectionButton = new Button
        (
            playerCountSelectionMenu,
            windowWidth/2 - buttonWidth/2,
            playerCountSelectionButtonInitialPositionY + i*playerCountSelectionButtonDistanceBetweenButtonsY,
            buttonWidth,
            buttonHeight,
            &font,
            std::to_string(i),
            sf::Color::Green
        );
        playerCountSelectionButtons.push_back(numberOfPlayersSelectionButton);
    }
    
}

void playerCountSelectionButtonsEventHandler(sf::RenderWindow& window)
{
    for(int i=0;i<playerCountSelectionButtons.size();i++)
    {
        if(playerCountSelectionButtons[i]->isMouseOver(window))
        {
            playerCountSelectionMenu.hideAll();
            createPlayerSetupMenu(i+1);
        }
    }
}