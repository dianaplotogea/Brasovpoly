#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "UI/UIContainer.h"
#include "Menu/PlayerCountSelectionMenuHandler.h"
#include "Menu/PlayerSetupMenuHandler.h"
#include "Menu/PlayerColorSelector.h"
#include "CloseButtonHandler.h"
#include "Gameplay/GameplayHandler.h"
#include "Gameplay/InGameSceneCreator.h"
#include "Menu/TutorialMenuHandler.h"
#include "UI/ButtonHoverHandler.h"
#include "Globals.h"

CloseButtonHandler closeButtonHandler;
GameplayHandler gameplayHandler;
TutorialMenuHandler tutorialMenuHandler;
InGameSceneCreator inGameSceneCreator;
PlayerColorSelector playerColorSelector;
PlayerCountSelectionMenuHandler playerCountSelectionMenuHandler;
PlayerSetupMenuHandler playerSetupMenuHandler;


void createGUI()
{
    closeButtonHandler.createCloseButton();
    tutorialMenuHandler.createTutorialMenu();
    playerCountSelectionMenuHandler.createPlayerCountSelectionMenu();
    playerColorSelector.createColorSelectorMenu();
    playerSetupMenuHandler.createStartGameButton();
    inGameSceneCreator.createInGameScene();
}

void buttonClickEvents(sf::RenderWindow& window, sf::Event event)
{
    tutorialMenuHandler.tutorialButtonEventHandler(window);
    playerCountSelectionMenuHandler.playerCountSelectionButtonsEventHandler(window);
    closeButtonHandler.closePlayerSetupMenu(window);   
    playerSetupMenuHandler.selectPlayerSetupMenuInput(window, event);
    playerColorSelector.colorButtonEventHandler(window);     
    playerColorSelector.colorSelectorButtonEventHandler(window);
    gameplayHandler.startGameButtonEventHandler(window);
    gameplayHandler.rollDiceButtonEventHandler(window);
    gameplayHandler.buyPropertyButtonEventHandler(window);
    gameplayHandler.nextButtonEventHandler(window);
    gameplayHandler.buyHouseButtonEventHandler(window);
    
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(Globals::windowWidth, Globals::windowHeight), "Brasovpoly");

    if (!globals.getGlobalFont()->loadFromFile("Assets/arial.ttf"))
    {
        std::cerr << "Could not load font" << std::endl;
        return 1;
    }

    window.setVerticalSyncEnabled(true); // Enable V-sync, otherwise the GPU usage becomes really high

    createGUI();
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close(); // It is needed for the X button to work
            }
            
            ButtonHoverHandler ButtonHoverHandler;    
            ButtonHoverHandler.buttonHover(window);

            if (event.type == sf::Event::MouseButtonPressed)
            {
                buttonClickEvents(window, event);
            }
            else if (event.type == sf::Event::TextEntered)
            {
                playerSetupMenuHandler.handleEnteredTextSelectPlayerSetupMenu(event);
            }
        }

        window.clear();

        globals.getPlayerCountSelectionMenu().draw(window);
        globals.getTutorialMenu().draw(window);
        globals.getPlayerSetupMenu().draw(window);
        globals.getPlayerColorSelectorMenu().draw(window);
        globals.getInGameScene().draw(window);
        
        if(globals.getCurrentState() != Globals::GameState::PlayerCountSelection)
        {
            globals.getCloseButton()->draw(window);
            globals.getCloseButtonUISpritePlayerCountSelectionMenu()->draw(window);
        }

        window.display();
    }

    return 0;
}