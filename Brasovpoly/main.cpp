#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "UI/Button.h"
#include "UI/UIContainer.h"
#include "UI/UIText.h"
#include "PlayerCountSelectionMenuHandler.h"
#include "PlayerSetupMenuHandler.h"
#include "PlayerColorSelector.h"
#include "CloseButtonHandler.h"
#include "PlayerColorSelector.h"
#include "GameplayHandler.h"
#include "InGameSceneCreator.h"
#include "InGameSceneCreator.h"
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