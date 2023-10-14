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
#include "Globals.h"

void createGUI()
{
    createCloseButton();
    createPlayerCountSelectionMenu();
    createColorSelectorMenu();
    createStartGameButton();
    createInGameScene();
}

void buttonEventHandling(sf::RenderWindow& window, sf::Event event)
{
    playerCountSelectionButtonsEventHandler(window);
    closePlayerSetupMenu(window);   
    selectPlayerSetupMenuInput(window, event);
    colorButtonEventHandler(window);     
    colorSelectorButtonEventHandler(window);
    startGameButtonEventHandler(window);
    rollDiceButtonEventHandler(window);
    buyPropertyButtonEventHandler(window);
    nextButtonEventHandler(window);
    
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
                
            if (event.type == sf::Event::MouseButtonPressed)
            {
                buttonEventHandling(window, event);
            }
            else if (event.type == sf::Event::TextEntered)
            {
                handleEnteredTextSelectPlayerSetupMenu(event);
            }
        }

        window.clear();

        playerCountSelectionMenu.draw(window);
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