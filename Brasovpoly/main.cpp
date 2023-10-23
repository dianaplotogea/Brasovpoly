#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "UI/Button.h"
#include "UI/UIContainer.h"
#include "UI/UIText.h"
#include "Menu/PlayerCountSelectionMenuHandler.h"
#include "Menu/PlayerSetupMenuHandler.h"
#include "Menu/PlayerColorSelector.h"
#include "CloseButtonHandler.h"
#include "Gameplay/GameplayHandler.h"
#include "Gameplay/InGameSceneCreator.h"
#include "Menu/TutorialMenuHandler.h"
#include "UI/ButtonHoverHandler.h"
#include "Globals.h"

void createGUI()
{
    createCloseButton();
    createTutorialMenu();
    createPlayerCountSelectionMenu();
    createColorSelectorMenu();
    createStartGameButton();
    createInGameScene();
}

void buttonClickEvents(sf::RenderWindow& window, sf::Event event)
{
    tutorialButtonEventHandler(window);
    playerCountSelectionButtonsEventHandler(window);
    closePlayerSetupMenu(window);   
    selectPlayerSetupMenuInput(window, event);
    colorButtonEventHandler(window);     
    colorSelectorButtonEventHandler(window);
    startGameButtonEventHandler(window);
    rollDiceButtonEventHandler(window);
    buyPropertyButtonEventHandler(window);
    nextButtonEventHandler(window);
    buyHouseButtonEventHandler(window);
    
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Brasovpoly");

    if (!font.loadFromFile("Assets/arial.ttf"))
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
                
            buttonHover(window);

            if (event.type == sf::Event::MouseButtonPressed)
            {
                buttonClickEvents(window, event);
            }
            else if (event.type == sf::Event::TextEntered)
            {
                handleEnteredTextSelectPlayerSetupMenu(event);
            }
        }

        window.clear();

        playerCountSelectionMenu.draw(window);
        tutorialMenu.draw(window);
        playerSetupMenu.draw(window);
        playerColorSelectorMenu.draw(window);
        inGameScene.draw(window);
        
        if(currentState != GameState::PlayerCountSelection)
        {
            closeButton->draw(window);
            closeButtonUISpritePlayerCountSelectionMenu->draw(window);
        }

        window.display();
    }

    return 0;
}