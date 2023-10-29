#include "GameplayHandler.h"

#include "InGameSceneCreator.h"
#include "../Globals.h"
#include "GameOverHandler.h"
#include "TimeHandler.h"
#include "TransportProperty.h"
#include "GoToJailLocation.h"
#include "JailLocation.h"
#include "TaxLocation.h"
#include "GamblingLocation.h"
#include <iostream>
#include <random>
#include <SFML/System/Clock.hpp>



int GameplayHandler::getPercentOfPropertyPriceWhichHasToBePaidWhenPropertyIsVisited()
{
    return percentOfPropertyPriceWhichHasToBePaidWhenPropertyIsVisited;
}

void GameplayHandler::createPlayerRectangles()
{
    int rectangleIndex = 0;
    int playerPositionY = globals.getLocations()[0]->position.y + initialPlayerPositionY;
    for(int numberOfRows = 0; numberOfRows<globals.getPlayers().size()/numberOfColumnsPlayerRectangles+1; numberOfRows++)
    {
        for(int i=0;i<numberOfColumnsPlayerRectangles;i++)
        {
            if(rectangleIndex == globals.getPlayers().size())
            {
                break;
            }
            UIRectangleShape* uiRectangleShapePlayer = new UIRectangleShape
            (
                globals.getInGameScene(),
                sf::Vector2f(globals.getLocations()[0]->position.x + initialPlayerPositionX + i*(distanceBetweenPlayersX + uiRectangleShapePlayerSize), playerPositionY),  
                sf::Vector2f(uiRectangleShapePlayerSize, uiRectangleShapePlayerSize),
                globals.getPlayers()[rectangleIndex]->getColor()
            );
            globals.getPlayers()[rectangleIndex++]->setUiRectangleShapePlayer(uiRectangleShapePlayer);
            globals.getInGameSceneUIElementsThatMustBeDeleted().push_back(uiRectangleShapePlayer);
        }
        playerPositionY += distanceBetweenPlayersY + uiRectangleShapePlayerSize;
    }
}

void GameplayHandler::createPlayerInfoTexts()
{
    int playerNameTextIndex = 0;
    int playerNameTextPositionY = playerNameTextIntialPositionY;
    for(int numberOfRows = 0; numberOfRows<globals.getPlayers().size()/numberOfColumnsPlayerInfoTexts+1; numberOfRows++)
    {
        for(int i=0;i<numberOfColumnsPlayerInfoTexts;i++)
        {
            if(playerNameTextIndex == globals.getPlayers().size())
            {
                break;
            }
            std::cout << "if(playerNameTextIndex == players.size())" <<std::endl;
            UIText* playerNameText = new UIText(globals.getInGameScene(), globals.getGlobalFont(), playerNameTextCharacterSize, globals.getPlayers()[playerNameTextIndex]->getName(), globals.getPlayers()[playerNameTextIndex]->getColor());
            playerNameText->setPosition(sf::Vector2f(playerNameTextPositionX + i * distanceBetweenPlayerNameTextsX, playerNameTextPositionY));
            globals.getInGameSceneUIElementsThatMustBeDeleted().push_back(playerNameText);
            std::cout << "inGameSceneUIElementsThatMustBeDeleted.push_back(playerNameText);" <<std::endl;
            UIText* playerMoneyAmountText = new UIText(globals.getInGameScene(), globals.getGlobalFont(), playerNameTextCharacterSize, std::to_string(initialMoneyAmount) + "RON", globals.getPlayers()[playerNameTextIndex]->getColor());
            playerMoneyAmountText->setPosition(sf::Vector2f(playerNameTextPositionX + i * distanceBetweenPlayerNameTextsX, playerNameTextPositionY + playerMoneyAmountTextPositionY));
            globals.getInGameSceneUIElementsThatMustBeDeleted().push_back(playerMoneyAmountText);

            UIText* playerProfitAmountText = new UIText(globals.getInGameScene(), globals.getGlobalFont(), playerNameTextCharacterSize, "", globals.getPlayers()[playerNameTextIndex]->getColor());
            playerProfitAmountText->setPosition(sf::Vector2f(playerNameTextPositionX + i * distanceBetweenPlayerNameTextsX, playerNameTextPositionY + playerMoneyAmountTextPositionY + playerProfitAmountTextPositionY));
            globals.getInGameSceneUIElementsThatMustBeDeleted().push_back(playerProfitAmountText);
            std::cout << "inGameSceneUIElementsThatMustBeDeleted.push_back(playerProfitAmountText);" << std::endl;
            globals.getPlayers()[playerNameTextIndex]->setMoneyAmount(initialMoneyAmount);
            std::cout << "players[playerNameTextIndex]->setMoneyAmount(initialMoneyAmount);" << std::endl;
            //players[playerNameTextIndex]->moneyAmount = initialMoneyAmount;
            globals.getPlayers()[playerNameTextIndex]->setPlayerNameText(playerNameText);
            globals.getPlayers()[playerNameTextIndex]->setPlayerMoneyAmountText(playerMoneyAmountText);
            globals.getPlayers()[playerNameTextIndex]->setPlayerProfitAmountText(playerProfitAmountText);
            globals.getPlayers()[playerNameTextIndex]->setCurrentLocation(globals.getLocations()[0]); // Start

            playerNameTextIndex++;
        }
        playerNameTextPositionY += distanceBetweenPlayerNameTextsY;
    }
}

void GameplayHandler::resizeCurrentPlayerInfoTexts()
{
    if(!currentPlayerWhichHasToThrow->getIsInJail())
    {
        currentPlayerWhichHasToThrow->getPlayerNameText()->setCharacterSize(currentPlayerNameTextCharacterSize);
    }
    if(previousPlayer != nullptr)
    {
        previousPlayer->getPlayerNameText()->setCharacterSize(playerNameTextCharacterSize);
    }
    std::cout << "GameplayHandler::resizeCurrentPlayerInfoTexts()" << std::endl;

}

void GameplayHandler::startGameButtonEventHandler(sf::RenderWindow& window)
{
    if(globals.getStartGameButton()->isMouseOver(window))
    {
        std::cout << "if(startGameButton->isMouseOver(window))" << std::endl;
        Property* firstProperty = dynamic_cast<Property*>(globals.getLocations()[1]);
        if(firstProperty)
        {
            firstProperty->setOwner(nullptr); // It should be nullptr by default because it's set in the constructor, but for this particular property it's not
        }
        else
        {
            std::cerr << "First location is not property" << std::endl;
        }
        globals.getPlayerSetupMenu().hideAll();
        globals.getInGameScene().showAll();
        globals.getBuyPropertyButton()->setVisible(false);
        globals.getNextButton()->setVisible(false);
        globals.getBuyHouseButton()->setVisible(false);
        globals.getGameOverText()->setVisible(false);
        globals.getInGameClockText()->setVisible(false);
        globals.setCurrentState(Globals::GameState::InGame);
        std::cout << "currentState = GameState::InGame;" << std::endl;
        createPlayerInfoTexts();
        std::cout << "createPlayerInfoTexts();" << std::endl;
        createPlayerRectangles();
        std::cout << "createPlayerRectangles();" << std::endl;
        currentPlayerIndex = 0; // It has to be resetted to 0, in case the game was restarted
        currentPlayerWhichHasToThrow = globals.getPlayers()[currentPlayerIndex];
        resizeCurrentPlayerInfoTexts();
        startInGameClock();

    }
}

void GameplayHandler::moveToNextPlayer()
{
    globals.getNextButton()->setVisible(false);
    globals.getRollDiceButton()->setVisible(true);
    globals.getBuyPropertyButton()->setVisible(false);
    globals.getBuyHouseButton()->setVisible(false);
    previousPlayer = currentPlayerWhichHasToThrow;
    currentPlayerIndex++;
    if(currentPlayerIndex >= globals.getPlayers().size())
    {
        currentPlayerIndex = 0;
    }
    std::cout << "currentPlayerIndex: " << currentPlayerIndex << std::endl;
    currentPlayerWhichHasToThrow = globals.getPlayers()[currentPlayerIndex];
    
    if(currentPlayerWhichHasToThrow->getIsInJail())
    {
        currentPlayerWhichHasToThrow->incrementNumberOfTurnsSinceJail();
        if(currentPlayerWhichHasToThrow->getNumberOfTurnsSinceJail() == numberOfSkippedTurnsWhenPlayerisInJail+1) // Player comes out from jail
        {
            currentPlayerWhichHasToThrow->setNumberOfTurnsSinceJail(0);
            currentPlayerWhichHasToThrow->setIsInJail(false);
            currentPlayerWhichHasToThrow->getUiRectangleShapePlayer()->setColor(currentPlayerWhichHasToThrow->getColor());
        }
        else // Player is skipped because of jail
        {
            std::cout << "Player is skipped because of jail" << std::endl;
            resizeCurrentPlayerInfoTexts();
            moveToNextPlayer();
        }
    }
    resizeCurrentPlayerInfoTexts();
}

int getRadnomNumberBetweenTwoNumbersInclusive(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

void GameplayHandler::removeCurrentPlayer()
{
    for(Location* location : currentPlayerWhichHasToThrow->getOwnedProperties())
    {
        Property* property = dynamic_cast<Property*>(location);

        if(property)
        {
            property->getPropertyColorSquare()->setColor(sf::Color::Black);
            property->setOwner(nullptr);
        }
    }

    auto it = std::find(globals.getPlayers().begin(), globals.getPlayers().end(), currentPlayerWhichHasToThrow);

    int indexOfCurrentPlayerWhichHasToThrow;
    if (it != globals.getPlayers().end())
    {
        indexOfCurrentPlayerWhichHasToThrow = std::distance(globals.getPlayers().begin(), it);

    }

    for(int i=globals.getPlayers().size()-1; i > indexOfCurrentPlayerWhichHasToThrow; i--)
    {
        globals.getPlayers()[i]->getPlayerNameText()->setPosition(globals.getPlayers()[i-1]->getPlayerNameText()->getPosition());
        globals.getPlayers()[i]->getPlayerMoneyAmountText()->setPosition(globals.getPlayers()[i-1]->getPlayerMoneyAmountText()->getPosition());
        globals.getPlayers()[i]->getPlayerProfitAmountText()->setPosition(globals.getPlayers()[i-1]->getPlayerProfitAmountText()->getPosition());

    }

    globals.getPlayers().erase(it);

    std::vector<UIElement*> elementsToRemove =
    {
        currentPlayerWhichHasToThrow->getPlayerNameText(),
        currentPlayerWhichHasToThrow->getPlayerMoneyAmountText(),
        currentPlayerWhichHasToThrow->getPlayerProfitAmountText(),
        currentPlayerWhichHasToThrow->getUiRectangleShapePlayer()
    };

    for (UIElement* element : elementsToRemove)
    {
        auto it = std::find(globals.getInGameScene().getElements().begin(), globals.getInGameScene().getElements().end(), element);

        if (it != globals.getInGameScene().getElements().end())
        {
            delete *it;
            globals.getInGameScene().getElements().erase(it);

        }
    }

    globals.getPlayersInWinningOrder().insert(globals.getPlayersInWinningOrder().begin(), currentPlayerWhichHasToThrow);
    if(globals.getPlayers().size() == 1)
    {
        GameOverHandler gameOverHandler;
        gameOverHandler.gameOver();
        return;
    }
}

bool GameplayHandler::hasPlayerLost(Player* player, int amountToPay)
{
    if(player->getMoneyAmount() - amountToPay <=0) // Player has lost
    {
        removeCurrentPlayer();
        return true;
    }
    return false;
}

void GameplayHandler::rollDiceButtonEventHandler(sf::RenderWindow& window)
{
    if(globals.getRollDiceButton()->isMouseOver(window))
    {
        auto it = std::find(globals.getLocations().begin(), globals.getLocations().end(), currentPlayerWhichHasToThrow->getCurrentLocation());
        if(it != globals.getLocations().end())
        {
            int rollDiceResult = getRadnomNumberBetweenTwoNumbersInclusive(rollDiceResultMin, rollDiceResultMax);
            globals.getRollDiceResultText()->setString(std::to_string(rollDiceResult));
            for(Player* player: globals.getPlayers())
            {
                player->getPlayerProfitAmountText()->setString("");
            }
            if(previousPlayerWhoGotMoneyFromOwningProperty != nullptr)
            {
                previousPlayerWhoGotMoneyFromOwningProperty->getPlayerProfitAmountText()->setString("");

            }
            
            int currentLocationIndex = std::distance(globals.getLocations().begin(), it);
            currentLocationIndex += rollDiceResult;
            if(currentLocationIndex >= globals.getLocations().size()) // start
            {
                currentLocationIndex -= globals.getLocations().size();
                if(hasPlayerLost(currentPlayerWhichHasToThrow, amountOfMoneyGotByAPlayerAfterItGoesTroughStart))
                {
                    return;
                }
                currentPlayerWhichHasToThrow->setMoneyAmount(currentPlayerWhichHasToThrow->getMoneyAmount() + amountOfMoneyGotByAPlayerAfterItGoesTroughStart);

                currentPlayerWhichHasToThrow->getPlayerProfitAmountText()->setString(std::to_string(amountOfMoneyGotByAPlayerAfterItGoesTroughStart));
                currentPlayerWhichHasToThrow->getPlayerMoneyAmountText()->setString(std::to_string(currentPlayerWhichHasToThrow->getMoneyAmount()) + "RON");
            }

            sf::Vector2f previousLocationPosition = currentPlayerWhichHasToThrow->getCurrentLocation()->position;
            sf::Vector2f currentLocationPosition = globals.getLocations()[currentLocationIndex]->position;
            sf::Vector2f previousUiRectangleShapePlayerPosition = currentPlayerWhichHasToThrow->getUiRectangleShapePlayer()->getPosition();
            sf::Vector2f uiRectangleShapePlayerPositionOffset = sf::Vector2f(previousUiRectangleShapePlayerPosition.x - previousLocationPosition.x, previousUiRectangleShapePlayerPosition.y - previousLocationPosition.y );
            currentPlayerWhichHasToThrow->getUiRectangleShapePlayer()->setPosition(sf::Vector2f(currentLocationPosition.x + uiRectangleShapePlayerPositionOffset.x, currentLocationPosition.y + uiRectangleShapePlayerPositionOffset.y));
            currentPlayerWhichHasToThrow->setCurrentLocation(globals.getLocations()[currentLocationIndex]);
            globals.getNextButton()->setVisible(true);
            globals.getRollDiceButton()->setVisible(false);
            currentProperty = dynamic_cast<Property*>(globals.getLocations()[currentLocationIndex]);
            if(currentProperty && currentPlayerWhichHasToThrow->getMoneyAmount()>currentProperty->getPrice() && currentProperty->getOwner() == nullptr) // Player can buy property
            {
                globals.getBuyPropertyButton()->setVisible(true);

            }
            else if(currentProperty && currentProperty->getOwner() != nullptr && currentProperty->getOwner() == currentPlayerWhichHasToThrow) // the property is owned by the player who went there
            { 
                currentRealEstate = dynamic_cast<RealEstate*>(currentProperty);
                if(currentRealEstate) // It's a real estate (houses can be bought)
                {
                    activateBuyHouseButtonIfPlayerCanBuyIt();
                }
                    
            }
            else
            {
                if(currentProperty && currentProperty->getOwner() != nullptr && currentProperty->getOwner() != currentPlayerWhichHasToThrow) // Player has to pay
                {
                    int amountToPay = 0;
                    if(dynamic_cast<TransportProperty*>(currentProperty))
                    {
                        amountToPay = currentProperty->getPrice()*percentOfPropertyPriceWhichHasToBePaidWhenPropertyIsVisited/100 * currentProperty->getOwner()->getTransportPropertyAmount(); // If the property is a transport type, the visitor has to pay the usual amount * the number of transport ptoprties owned by the owner
                    }
                    else
                    {
                        currentRealEstate = dynamic_cast<RealEstate*>(currentProperty);
                        if(currentRealEstate)
                        {
                            amountToPay = currentRealEstate->getPrice()*percentOfPropertyPriceWhichHasToBePaidWhenPropertyIsVisited/100 + currentRealEstate->getHouseAmount() * currentRealEstate->getPrice()*percentOfRealEstatePriceWhichHasToBePaidPerHouseWhenRealEstateIsVisited/100;
                        }
                    }
                    if(hasPlayerLost(currentPlayerWhichHasToThrow, amountToPay))
                    {
                        return;
                    }
                    currentPlayerWhichHasToThrow->setMoneyAmount(currentPlayerWhichHasToThrow->getMoneyAmount() - amountToPay);
                    currentPlayerWhichHasToThrow->getPlayerProfitAmountText()->setString("-" + std::to_string(amountToPay));
                    currentPlayerWhichHasToThrow->getPlayerMoneyAmountText()->setString(std::to_string(currentPlayerWhichHasToThrow->getMoneyAmount()) + "RON");

                    currentProperty->getOwner()->setMoneyAmount(currentProperty->getOwner()->getMoneyAmount() + amountToPay);
                    currentProperty->getOwner()->getPlayerProfitAmountText()->setString("+" + std::to_string(amountToPay));
                    currentProperty->getOwner()->getPlayerMoneyAmountText()->setString(std::to_string(currentProperty->getOwner()->getMoneyAmount()) + "RON");
                    previousPlayerWhoGotMoneyFromOwningProperty = currentProperty->getOwner();

                }
                else if(!currentProperty) // Start, Jail, GoToJail, Tax, Gambling
                {
                    if(dynamic_cast<GoToJailLocation*>(globals.getLocations()[currentLocationIndex])) // Go to jail
                    {
                        currentPlayerWhichHasToThrow->setIsInJail(true);
                        currentPlayerWhichHasToThrow->getUiRectangleShapePlayer()->setPosition(sf::Vector2f(globals.getLocations()[20]->position.x + uiRectangleShapePlayerPositionOffset.x, globals.getLocations()[20]->position.y + uiRectangleShapePlayerPositionOffset.y));
                        currentPlayerWhichHasToThrow->setCurrentLocation(globals.getLocations()[20]);
                        sf::Color colorOfPlayerInJail = sf::Color(currentPlayerWhichHasToThrow->getColor().r, currentPlayerWhichHasToThrow->getColor().g, currentPlayerWhichHasToThrow->getColor().b, colorOfPlayerInJailAlphaValue);
                        currentPlayerWhichHasToThrow->getUiRectangleShapePlayer()->setColor(colorOfPlayerInJail);
                        std::cout << "Go to jail" << std::endl;
                    }
                    else if(dynamic_cast<JailLocation*>(globals.getLocations()[currentLocationIndex])) // Visiting jail
                    {
                        std::cout << "Jail" << std::endl;
                    }
                    else if(dynamic_cast<TaxLocation*>(globals.getLocations()[currentLocationIndex])) // Tax
                    {
                        std::cout << "Anaf" << std::endl;
                        for(Player* player : globals.getPlayers())
                        {
                            if(hasPlayerLost(player, taxLocationAmount))
                            {
                                return;
                            }

                            player->setMoneyAmount(player->getMoneyAmount() - taxLocationAmount);
                            player->getPlayerProfitAmountText()->setString("-" + std::to_string(taxLocationAmount));
                            player->getPlayerMoneyAmountText()->setString(std::to_string(player->getMoneyAmount()) + "RON");

                        }
                    }
                    else if(dynamic_cast<GamblingLocation*>(globals.getLocations()[currentLocationIndex])) // Gambling
                    {
                        std::cout << "GamblingLocation" << std::endl;
                        int gamblingResult = getRadnomNumberBetweenTwoNumbersInclusive(minimumGamblingAmountProfit, maximumGamblingAmountProfit);
                        if(hasPlayerLost(currentPlayerWhichHasToThrow, gamblingResult))
                        {
                            return;
                        }
                        currentPlayerWhichHasToThrow->setMoneyAmount(currentPlayerWhichHasToThrow->getMoneyAmount() + gamblingResult);
                        currentPlayerWhichHasToThrow->getPlayerProfitAmountText()->setString(std::to_string(gamblingResult));
                        currentPlayerWhichHasToThrow->getPlayerMoneyAmountText()->setString(std::to_string(currentPlayerWhichHasToThrow->getMoneyAmount()) + "RON");

                    }
                }
                
                moveToNextPlayer();
                    
            }
            nextButtonActivatorClock.restart();

        }
    }
}

void GameplayHandler::buyPropertyButtonEventHandler(sf::RenderWindow& window)
{
    if(globals.getBuyPropertyButton()->isMouseOver(window))
    {
        currentPlayerWhichHasToThrow->addProperty(currentProperty);
        currentPlayerWhichHasToThrow->setMoneyAmount(currentPlayerWhichHasToThrow->getMoneyAmount() - currentProperty->getPrice());
        currentProperty->setOwner(currentPlayerWhichHasToThrow);
        currentProperty->getPropertyColorSquare()->setColor(currentPlayerWhichHasToThrow->getColor());
        currentPlayerWhichHasToThrow->getPlayerMoneyAmountText()->setString(std::to_string(currentPlayerWhichHasToThrow->getMoneyAmount()) + "RON");
        currentPlayerWhichHasToThrow->getPlayerProfitAmountText()->setString("-" + std::to_string(currentProperty->getPrice()));
        
        if(dynamic_cast<TransportProperty*>(currentProperty))
        {
            currentPlayerWhichHasToThrow->incrementTransportPropertyAmount();
        }

        moveToNextPlayer();
    }
}

void GameplayHandler::nextButtonEventHandler(sf::RenderWindow& window)
{
    if(nextButtonActivatorClock.getElapsedTime().asSeconds() < delayAfterWhichNextButtonBecomesPressableAfterBuyPropertyButtonWasPressed) // a small delay has to be added, because otherwise the nextButton is pressed at the same time when the rollDiceButton is pressed
    {
        return;
    }
    if(globals.getNextButton()->isMouseOver(window))
    {
        moveToNextPlayer();
    }    
}

void moveElementBeforePlayerRectangleShapes(UIElement* uiElement)
{
    auto it = std::find(globals.getInGameScene().getElements().begin(), globals.getInGameScene().getElements().end(), uiElement);
    if (it != globals.getInGameScene().getElements().end())
    {
        auto new_pos = globals.getInGameScene().getElements().end() - globals.getPlayers().size() - 1;
        if (it < new_pos)
            std::rotate(it, it + 1, new_pos + 1);  // Move element to the right
        else
            std::rotate(new_pos, it, it + 1);  // Move element to the left
        }
    else
    {
        std::cout << "Object not found in the vector." << std::endl;
    }     
}

void GameplayHandler::buyHouseButtonEventHandler(sf::RenderWindow& window)
{
    if(globals.getBuyHouseButton()->isMouseOver(window))
    {
        currentRealEstate->incrementHouseAmount();
        int housePrice = currentProperty->getPrice()*percentOfRealEstatePriceWhichHasToBePaidToBuyAHouse/100;
        currentPlayerWhichHasToThrow->setMoneyAmount(currentPlayerWhichHasToThrow->getMoneyAmount() - housePrice);
        currentPlayerWhichHasToThrow->getPlayerProfitAmountText()->setString("-" + std::to_string(housePrice));
        currentPlayerWhichHasToThrow->getPlayerMoneyAmountText()->setString(std::to_string(currentPlayerWhichHasToThrow->getMoneyAmount()) + "RON");        

        //if(currentRealEstate->getHouseAmount() == numberOfHousesAfterWhichItsConsideredHotel)
       // {
            /*
            std::cout << "if(currentRealEstate->getHouseAmount() == numberOfHousesAfterWhichItsConsideredHotel)" << std::endl;
            for(auto it = globals.inGameScene.getElements().begin(); it != globals.inGameScene.getElements().end();)
            {
                auto sprite = dynamic_cast<UISprite*>(*it);
                if(std::find(currentRealEstate->getHouseSprites().begin(), currentRealEstate->getHouseSprites().end(), sprite) != currentRealEstate->getHouseSprites().end())
                {
                    delete sprite;
                    it = globals.inGameScene.getElements().erase(it);
                }
                else
                {
                    ++it;
                }
            }

            currentRealEstate->clearHouseSprites();
            std::cout << "currentRealEstate->clearHouseSprites();" << std::endl;
            if(!hotelTexture.loadFromFile("Assets/Hotel.png"))
            {
                std::cerr << "Failed to load image" << std::endl;
            }
            UISprite* hotelSprite = new UISprite
            (
                globals.inGameScene,
                &hotelTexture,
                sf::Vector2f
                (
                    currentRealEstate->getPropertyColorSquare()->getPosition().x + (Globals::locationSize - hotelSpriteSize)/2,
                    currentRealEstate->getPropertyColorSquare()->getPosition().y + hotelSpritePositionY
                ),
                sf::Vector2f(hotelSpriteSize, hotelSpriteSize)
            );
            std::cout << "moveElementBeforePlayerRectangleShapes(hotelSprite);" << std::endl;
            //moveElementBeforePlayerRectangleShapes(hotelSprite); // It has to be moved before the uiRectangleShapePlayer, otherwise the uiRectangleShapePlayer will be beneath the sprite. The players were the last objects that were added into inGameScene.elements

            globals.inGameSceneUIElementsThatMustBeDeleted.push_back(hotelSprite);
        }
        else
        {
            */
            if(!houseTexture.loadFromFile("Assets/House.png"))
            {
                std::cerr << "Failed to load image" << std::endl;
            }

            UISprite* houseSprite = new UISprite
            (
                globals.getInGameScene(),
                &houseTexture,
                sf::Vector2f
                (
                    currentRealEstate->getPropertyColorSquare()->getPosition().x + currentRealEstate->getHouseAmount() * (Globals::locationSize - 3 * houseSpriteSize )/4 + (currentRealEstate->getHouseAmount()-1) * houseSpriteSize,
                    currentRealEstate->getPropertyColorSquare()->getPosition().y + houseSpritePositionY
                ),
                sf::Vector2f(houseSpriteSize, houseSpriteSize)
            );

            moveElementBeforePlayerRectangleShapes(houseSprite); // It has to be moved before the uiRectangleShapePlayer, otherwise the uiRectangleShapePlayer will be beneath the sprite. The players were the last objects that were added into inGameScene.elements

            globals.getInGameSceneUIElementsThatMustBeDeleted().push_back(houseSprite);
            currentRealEstate->addHouseSprite(houseSprite);
            
        //}
        activateBuyHouseButtonIfPlayerCanBuyIt();

    }
}

void GameplayHandler::activateBuyHouseButtonIfPlayerCanBuyIt()
{
    int housePrice = currentRealEstate->getPrice()*percentOfRealEstatePriceWhichHasToBePaidToBuyAHouse/100;
    if(currentPlayerWhichHasToThrow->getMoneyAmount() > housePrice && currentRealEstate->getHouseAmount() < numberOfHousesAfterWhichItsConsideredHotel)
    {
        globals.getBuyHouseButton()->setVisible(true);
        
        if(currentRealEstate->getHouseAmount() == numberOfHousesAfterWhichItsConsideredHotel-1)
        {
            globals.getBuyHouseButton()->getText().setString("Buy hotel(" + std::to_string(housePrice) + ")");
            globals.getBuyHouseButton()->centerText();
        }
        else
        {
            globals.getBuyHouseButton()->getText().setString("Buy house(" + std::to_string(housePrice) + ")");
            globals.getBuyHouseButton()->centerText();
        }
    }
    else
    {
        moveToNextPlayer();
    }
}