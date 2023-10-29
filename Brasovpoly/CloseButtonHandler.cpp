#include <iostream>
#include "CloseButtonHandler.h"
#include "Globals.h"
#include "UI/Button.h"
#include "UI/UiSprite.h"
#include "UI/UIRectangleShape.h"
#include "UI/UIText.h"
#include "Gameplay/RealEstate.h"
#include "Menu/PlayerSetupMenuHandler.h"



void CloseButtonHandler::createCloseButton()
{   
    if(!closeButtonTexture.loadFromFile("Assets/BackButton.png"))
    {
        std::cerr << "Failed to load image" << std::endl;
    }
    globals.setCloseButton(new Button(globals.getEmptyUIContainer(), closeButtonPadding, closeButtonPadding, closeButtonSize, closeButtonSize));
    globals.setCloseButtonUISpritePlayerCountSelectionMenu(new UISprite(globals.getEmptyUIContainer(), &closeButtonTexture, sf::Vector2f(closeButtonPadding, closeButtonPadding), sf::Vector2f(closeButtonSize, closeButtonSize)));
    globals.getCloseButton()->setUiSprite(globals.getCloseButtonUISpritePlayerCountSelectionMenu());
    globals.getSpriteColorHoverButtons().push_back(globals.getCloseButton());
    
}

void resetPlayerSetupMenu()
{
    std::cout << "resetPlayerSetupMenu()" << std::endl;
    globals.getPlayers().clear();
    std::vector<UIElement*> uiElements = globals.getPlayerSetupMenu().getElements();
    std::cout << "std::vector<UIElement*> uiElements = playerSetupMenu.getElements();" << std::endl;
    for(UIElement* uiElement : uiElements)
    {
        if(uiElement == globals.getStartGameButton())
        {
            continue;
        }
        auto it = std::find(globals.getOutlineColorHoverButtons().begin(), globals.getOutlineColorHoverButtons().end(), uiElement);
        if(it != globals.getOutlineColorHoverButtons().end())
        {
            globals.getOutlineColorHoverButtons().erase(it);
            
        }
        delete uiElement;
        
                    
    }
    globals.getPlayerSetupMenu().clearElements();
    std::cout << "playerSetupMenu.clearElements();" << std::endl;
    globals.getPlayerCountSelectionMenu().showAll();
    globals.setCurrentState(Globals::GameState::PlayerCountSelection);
    globals.setShouldStartGameButtonBeActivated(false);
    PlayerSetupMenuHandler playerSetupMenuHandler;
    playerSetupMenuHandler.createStartGameButton(); // This shouldn't be here, but the startGameButton is somehow destroyed and won't appear otherwise
}

void CloseButtonHandler::closePlayerSetupMenu(sf::RenderWindow& window)
{
    if(globals.getCloseButton()->isMouseOver(window))
    {
        switch(globals.getCurrentState())
        {
            case Globals::GameState::PlayerSetup:
            {
                std::cout << "Back from PlayerSetup menu" << std::endl;
                resetPlayerSetupMenu();
                break;
            }
            case Globals::GameState::TutorialMenu:
            {
                std::cout << "Back from Tutorial menu" << std::endl;
                globals.setCurrentState(Globals::GameState::PlayerCountSelection);
                globals.getPlayerCountSelectionMenu().showAll();
                globals.getTutorialMenu().hideAll();
                break;
            }
            case Globals::GameState::PlayerColorSelection:
            {
                globals.getPlayerSetupMenu().showAll();
                globals.getPlayerColorSelectorMenu().hideAll();
                globals.setCurrentState(Globals::GameState::PlayerSetup);
                PlayerSetupMenuHandler playerSetupMenuHandler;
                playerSetupMenuHandler.activateStartGameButtonIfAllPlayersAreSet();
                break;
            }
            case::Globals::GameState::InGame:
            {
                globals.getInGameScene().hideAll();
                for(Location* location : globals.getLocations())
                {
                    Property* property = dynamic_cast<Property*>(location); 
                    if(property)
                    {
                        property->setOwner(nullptr);
                    }       
                    
                    RealEstate* realEstate = dynamic_cast<RealEstate*>(location);
                    if(realEstate)
                    {
                        realEstate->clearHouseSprites();
                    }
                }
                resetPlayerSetupMenu();
                std::vector<UIElement*>::iterator it = globals.getInGameScene().getElements().begin();
                while (it != globals.getInGameScene().getElements().end()) 
                {
                    if(std::find(globals.getInGameSceneUIElementsThatMustBeDeleted().begin(), globals.getInGameSceneUIElementsThatMustBeDeleted().end(), *it) != globals.getInGameSceneUIElementsThatMustBeDeleted().end()) 
                    {
                        delete *it;
                        it = globals.getInGameScene().getElements().erase(it);
                    } 
                    else 
                    {
                        ++it;
                    }
                }
                globals.getInGameSceneUIElementsThatMustBeDeleted().clear();

                for(UIRectangleShape* propertyColorSquare : globals.getPropertyColorSquares())
                {
                    propertyColorSquare->setColor(sf::Color::Black);
                }

                globals.getRollDiceResultText()->setString("");
                globals.getLeaderBoardNameTexts().clear();
                globals.getGameOverPlayingTimeText()->setString("");
                globals.setShouldInGameClockWork(false);
                
                break;
        
            }
        }
    }
}