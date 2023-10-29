#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "../UI/Button.h"
#include "../UI/UIText.h"
#include "PlayerCountSelectionMenuHandler.h"
#include "PlayerSetupMenuHandler.h"
#include "../Globals.h"



void PlayerCountSelectionMenuHandler::createPlayerCountSelectionMenu()
{
    UIText* playerCountSelectionText = new UIText(globals.getPlayerCountSelectionMenu(), globals.getGlobalFont(), playerCountSelectionTextCharacterSize, "Select the number of players:");
    playerCountSelectionText->setPosition(sf::Vector2f(Globals::windowWidth/2 - playerCountSelectionText->getLocalBounds().width/2, playerCountSelectionTextPositionY));

    for(int i=2;i<maximumNumberOfPlayers+1;i++)
    {
        Button* numberOfPlayersSelectionButton = new Button
        (
            globals.getPlayerCountSelectionMenu(),
            Globals::windowWidth/2 - Globals::buttonWidth/2,
            playerCountSelectionButtonInitialPositionY + i*playerCountSelectionButtonDistanceBetweenButtonsY,
            Globals::buttonWidth,
            Globals::buttonHeight,
            globals.getGlobalFont(),
            std::to_string(i),
            globals.getButtonColor(),
            Globals::buttonBorderThickness,
            globals.getButtonBorderColor()
        );
        playerCountSelectionButtons.push_back(numberOfPlayersSelectionButton);
        globals.getOutlineColorHoverButtons().push_back(numberOfPlayersSelectionButton);
    }

    if(!tutorialButtonTexture.loadFromFile("Assets/Tutorial.png"))
    {
        std::cerr << "Failed to load image" << std::endl;
    }

    globals.setTutorialButton(new Button(globals.getPlayerCountSelectionMenu(), Globals::windowWidth - tutorialButtonPadding - tutorialButtonSize, tutorialButtonPadding, tutorialButtonSize, tutorialButtonSize ));
    globals.setTutorialButtonUISprite(new UISprite(globals.getPlayerCountSelectionMenu(), &tutorialButtonTexture, sf::Vector2f(Globals::windowWidth - tutorialButtonPadding - tutorialButtonSize, tutorialButtonPadding), sf::Vector2f(tutorialButtonSize, tutorialButtonSize) ));
    globals.getTutorialButton()->setUiSprite(globals.getTutorialButtonUISprite());
    globals.getSpriteColorHoverButtons().push_back(globals.getTutorialButton());
}

void PlayerCountSelectionMenuHandler::playerCountSelectionButtonsEventHandler(sf::RenderWindow& window)
{
    for(int i=0;i<playerCountSelectionButtons.size();i++)
    {
        if(playerCountSelectionButtons[i]->isMouseOver(window))
        {
            globals.getPlayerCountSelectionMenu().hideAll();
            PlayerSetupMenuHandler playerSetupMenuHandler;
            playerSetupMenuHandler.createPlayerSetupMenu(i+1);
        }
    }
}