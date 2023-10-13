#include "CloseButtonHandler.h"
#include "Globals.h"
#include "UI/Button.h"
#include "UI/UiSprite.h"
#include "UI/UIRectangleShape.h"
#include <iostream>
#include "PlayerSetupMenuHandler.h"

int closeButtonSize = 45;

sf::Texture texture;

void createCloseButton()
{   
    if (!texture.loadFromFile("Assets/BackButton.png"))
    {
        std::cerr << "Failed to load image" << std::endl;
    }
    closeButton = new Button(emptyUIContainer, 30, 30, closeButtonSize, closeButtonSize);
    closeButtonUISpritePlayerCountSelectionMenu = new UISprite(emptyUIContainer, &texture, sf::Vector2f(30, 30), sf::Vector2f(closeButtonSize, closeButtonSize));

}

void resetPlayerSetupMenu()
{
    players.clear();
    std::vector<UIElement*> uiElements = playerSetupMenu.elements;
    for(UIElement* uiElement : uiElements)
    {
        if(uiElement != startGameButton)
        {
            delete uiElement;
        }
                    
    }
    playerSetupMenu.elements.clear();
    playerCountSelectionMenu.showAll();
    currentState = GameState::PlayerCountSelection;
    shouldStartGameButtonBeActivated = false;
    createStartGameButton(); // This shouldn't be here, but the startGameButton is somehow destroyed and won't appear otherwise
}

void closePlayerSetupMenu(sf::RenderWindow& window)
{
    if(closeButton->isMouseOver(window))
    {
        switch(currentState)
        {
            case GameState::PlayerSetup:
            {
                resetPlayerSetupMenu();
                break;
            }
            case GameState::PlayerColorSelection:
            {
                std::cout << "BackFromColorSelection" <<std::endl;
                playerSetupMenu.showAll();
                playerColorSelectorMenu.hideAll();
                currentState = GameState::PlayerSetup;
                if(shouldStartGameButtonBeActivated)
                {
                    std::cout << "startGameButton->show();" <<std::endl;
                    startGameButton->show();
                }
                else
                {
                    startGameButton->hide(); // All the elements of playerSetupMenu are activated so this has to be deactivated
                }
                break;
            }
            case::GameState::InGame:
            {
                std::cout << "Back from InGame" <<std::endl;
                inGameScene.hideAll();
                resetPlayerSetupMenu();
    
                std::vector<UIElement*>::iterator it = inGameScene.elements.begin();
                while (it != inGameScene.elements.end()) 
                {
                    if(std::find(inGameSceneUIElementsThatMustBeDeleted.begin(), inGameSceneUIElementsThatMustBeDeleted.end(), *it) != inGameSceneUIElementsThatMustBeDeleted.end()) 
                    {
                        delete *it;
                        it = inGameScene.elements.erase(it);
                    } 
                    else 
                    {
                        ++it;
                    }
                }
                inGameSceneUIElementsThatMustBeDeleted.clear();

            }

        }

    }
}