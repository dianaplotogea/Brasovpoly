#include <iostream>
#include "CloseButtonHandler.h"
#include "Globals.h"
#include "UI/Button.h"
#include "UI/UiSprite.h"
#include "UI/UIRectangleShape.h"
#include "UI/UIText.h"
#include "Gameplay/RealEstate.h"
#include "Menu/PlayerSetupMenuHandler.h"

int closeButtonSize = 45;
int closeButtonPadding = 30;

sf::Texture closeButtonTexture;

void createCloseButton()
{   
    if(!closeButtonTexture.loadFromFile("Assets/BackButton.png"))
    {
        std::cerr << "Failed to load image" << std::endl;
    }
    closeButton = new Button(emptyUIContainer, closeButtonPadding, closeButtonPadding, closeButtonSize, closeButtonSize);
    closeButtonUISpritePlayerCountSelectionMenu = new UISprite(emptyUIContainer, &closeButtonTexture, sf::Vector2f(closeButtonPadding, closeButtonPadding), sf::Vector2f(closeButtonSize, closeButtonSize));
    closeButton->uiSprite = closeButtonUISpritePlayerCountSelectionMenu;
    spriteColorHoverButtons.push_back(closeButton);
    
}

void resetPlayerSetupMenu()
{
    players.clear();
    std::vector<UIElement*> uiElements = playerSetupMenu.elements;
    for(UIElement* uiElement : uiElements)
    {
        if(uiElement == startGameButton)
        {
            continue;
        }
        auto it = std::find(outlineColorHoverButtons.begin(), outlineColorHoverButtons.end(), uiElement);
        if(it != outlineColorHoverButtons.end())
        {
            outlineColorHoverButtons.erase(it);
            
        }
        delete uiElement;
        
                    
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
                std::cout << "Back from PlayerSetup menu" << std::endl;
                resetPlayerSetupMenu();
                break;
            }
            case GameState::TutorialMenu:
            {
                std::cout << "Back from Tutorial menu" << std::endl;
                currentState = GameState::PlayerCountSelection;
                playerCountSelectionMenu.showAll();
                tutorialMenu.hideAll();
                break;
            }
            case GameState::PlayerColorSelection:
            {
                playerSetupMenu.showAll();
                playerColorSelectorMenu.hideAll();
                currentState = GameState::PlayerSetup;
                activateStartGameButtonIfAllPlayersAreSet();
                break;
            }
            case::GameState::InGame:
            {
                inGameScene.hideAll();
                for(Location* location : locations)
                {
                    Property* property = dynamic_cast<Property*>(location); 
                    if(property)
                    {
                        property->owner = nullptr;
                    }       
                    
                    RealEstate* realEstate = dynamic_cast<RealEstate*>(location);
                    if(realEstate)
                    {
                        realEstate->houseSprites.clear();
                    }
                }
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

                for(UIRectangleShape* propertyColorSquare : propertyColorSquares)
                {
                    propertyColorSquare->setColor(sf::Color::Black);
                }

                rollDiceResultText->setString("");
                leaderBoardNameTexts.clear();
                gameOverPlayingTimeText->setString("");
                shouldInGameClockWork = false;
                
                break;
        
            }
        }
    }
}