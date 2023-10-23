#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "../UI/Button.h"
#include "../UI/UIText.h"
#include "PlayerCountSelectionMenuHandler.h"
#include "PlayerSetupMenuHandler.h"
#include "../Globals.h"

int maximumNumberOfPlayers = 6;
int playerCountSelectionButtonInitialPositionY = 150;
int playerCountSelectionButtonDistanceBetweenButtonsY = 100;
int playerCountSelectionTextPositionY = 200;
int playerCountSelectionTextCharacterSize = 30;

int tutorialButtonPadding = 30;
int tutorialButtonSize = 45;

std::vector<Button*> playerCountSelectionButtons;

sf::Texture tutorialButtonTexture;

void createPlayerCountSelectionMenu()
{
    UIText* playerCountSelectionText = new UIText(playerCountSelectionMenu, &font, playerCountSelectionTextCharacterSize, "Select the number of players:");
    playerCountSelectionText->setPosition(sf::Vector2f(windowWidth/2 - playerCountSelectionText->getLocalBounds().width/2, playerCountSelectionTextPositionY));

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
            buttonColor,
            buttonBorderThickness,
            buttonBorderColor
        );
        playerCountSelectionButtons.push_back(numberOfPlayersSelectionButton);
        outlineColorHoverButtons.push_back(numberOfPlayersSelectionButton);
    }

    if(!tutorialButtonTexture.loadFromFile("Assets/Tutorial.png"))
    {
        std::cerr << "Failed to load image" << std::endl;
    }

    tutorialButton = new Button(playerCountSelectionMenu, windowWidth - tutorialButtonPadding - tutorialButtonSize, tutorialButtonPadding, tutorialButtonSize, tutorialButtonSize );
    tutorialButtonUISprite = new UISprite(playerCountSelectionMenu, &tutorialButtonTexture, sf::Vector2f(windowWidth - tutorialButtonPadding - tutorialButtonSize, tutorialButtonPadding), sf::Vector2f(tutorialButtonSize, tutorialButtonSize) );
    tutorialButton->uiSprite = tutorialButtonUISprite;
    spriteColorHoverButtons.push_back(tutorialButton);
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