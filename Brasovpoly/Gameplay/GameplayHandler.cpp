#include "GameplayHandler.h"
#include "../UI/Button.h"
#include "../UI/UIRectangleShape.h"
#include "../UI/UIText.h"
#include "InGameSceneCreator.h"
#include "../Globals.h"
#include "GameOverHandler.h"
#include "TimeHandler.h"
#include "TransportProperty.h"
#include "RealEstate.h"
#include "GoToJailLocation.h"
#include "JailLocation.h"
#include "TaxLocation.h"
#include "GamblingLocation.h"
#include <iostream>
#include <random>
#include <SFML/System/Clock.hpp>

int uiRectangleShapePlayerSize = 30;
int initialPlayerPositionX = 15;
int initialPlayerPositionY = 55;
int distanceBetweenPlayersX = 15;
int distanceBetweenPlayersY = 5;
int numberOfColumnsPlayerRectangles = 3;

int numberOfColumnsPlayerInfoTexts = 3;
int playerNameTextCharacterSize = 35;
int currentPlayerNameTextCharacterSize = 58;
int playerNameTextPositionX = 275;
int playerNameTextIntialPositionY = 250;
int distanceBetweenPlayerNameTextsX = 300;
int distanceBetweenPlayerNameTextsY = 175;
int playerProfitAmountTextPositionY = 35;

int initialMoneyAmount = 3000;
int playerMoneyAmountTextPositionY = 68;

int currentPlayerIndex = 0;

int percentOfPropertyPriceWhichHasToBePaidWhenPropertyIsVisited = 20;

int rollDiceResultMin = 2;
int rollDiceResultMax = 12;

float delayAfterWhichNextButtonBecomesPressableAfterBuyPropertyButtonWasPressed = 0.1;

int percentOfRealEstatePriceWhichHasToBePaidToBuyAHouse = 20;
int percentOfRealEstatePriceWhichHasToBePaidPerHouseWhenRealEstateIsVisited = 10;
int numberOfHousesAfterWhichItsConsideredHotel = 4;
int numberOfHousesPerRow = 2;
int houseSpriteSize = 40;
int hotelSpriteSize = 80;
int houseSpritePositionY = 50;
int hotelSpritePositionY = 45;

int numberOfSkippedTurnsWhenPlayerisInJail = 3;

int colorOfPlayerInJailAlphaValue = 128;

int taxLocationAmount = 75; // ANAF

int minimumGamblingAmountProfit = -200;
int maximumGamblingAmountProfit = -100;

int amountOfMoneyGotByAPlayerAfterItGoesTroughStart = -10;

Player* currentPlayerWhichHasToThrow;
Player* previousPlayer;
Player* previousPlayerWhoGotMoneyFromOwningProperty;

Property* currentProperty;
RealEstate* currentRealEstate;

sf::Clock nextButtonActivatorClock;

sf::Texture houseTexture;
sf::Texture hotelTexture;

void createPlayerRectangles()
{
    int rectangleIndex = 0;
    int playerPositionY = locations[0]->position.y + initialPlayerPositionY;
    for(int numberOfRows = 0; numberOfRows<players.size()/numberOfColumnsPlayerRectangles+1; numberOfRows++)
    {
        for(int i=0;i<numberOfColumnsPlayerRectangles;i++)
        {
            if(rectangleIndex == players.size())
            {
                break;
            }
            UIRectangleShape* uiRectangleShapePlayer = new UIRectangleShape
            (
                inGameScene,
                sf::Vector2f(locations[0]->position.x + initialPlayerPositionX + i*(distanceBetweenPlayersX + uiRectangleShapePlayerSize), playerPositionY),  
                sf::Vector2f(uiRectangleShapePlayerSize, uiRectangleShapePlayerSize),
                players[rectangleIndex]->color
            );
            players[rectangleIndex++]->uiRectangleShapePlayer = uiRectangleShapePlayer;
            inGameSceneUIElementsThatMustBeDeleted.push_back(uiRectangleShapePlayer);
        }
        playerPositionY += distanceBetweenPlayersY + uiRectangleShapePlayerSize;
    }
}

void createPlayerInfoTexts()
{
    int playerNameTextIndex = 0;
    int playerNameTextPositionY = playerNameTextIntialPositionY;
    for(int numberOfRows = 0; numberOfRows<players.size()/numberOfColumnsPlayerInfoTexts+1; numberOfRows++)
    {
        for(int i=0;i<numberOfColumnsPlayerInfoTexts;i++)
        {
            if(playerNameTextIndex == players.size())
            {
                break;
            }
            UIText* playerNameText = new UIText(inGameScene, &font, playerNameTextCharacterSize, players[playerNameTextIndex]->name, players[playerNameTextIndex]->color);
            playerNameText->setPosition(sf::Vector2f(playerNameTextPositionX + i * distanceBetweenPlayerNameTextsX, playerNameTextPositionY));
            inGameSceneUIElementsThatMustBeDeleted.push_back(playerNameText);

            UIText* playerMoneyAmountText = new UIText(inGameScene, &font, playerNameTextCharacterSize, std::to_string(initialMoneyAmount) + "RON", players[playerNameTextIndex]->color);
            playerMoneyAmountText->setPosition(sf::Vector2f(playerNameTextPositionX + i * distanceBetweenPlayerNameTextsX, playerNameTextPositionY + playerMoneyAmountTextPositionY));
            inGameSceneUIElementsThatMustBeDeleted.push_back(playerMoneyAmountText);

            UIText* playerProfitAmountText = new UIText(inGameScene, &font, playerNameTextCharacterSize, "", players[playerNameTextIndex]->color);
            playerProfitAmountText->setPosition(sf::Vector2f(playerNameTextPositionX + i * distanceBetweenPlayerNameTextsX, playerNameTextPositionY + playerMoneyAmountTextPositionY + playerProfitAmountTextPositionY));
            inGameSceneUIElementsThatMustBeDeleted.push_back(playerProfitAmountText);

            players[playerNameTextIndex]->moneyAmount = initialMoneyAmount;
            players[playerNameTextIndex]->playerNameText = playerNameText;
            players[playerNameTextIndex]->playerMoneyAmountText = playerMoneyAmountText;
            players[playerNameTextIndex]->playerProfitAmountText = playerProfitAmountText;
            players[playerNameTextIndex]->currentLocation = locations[0]; // Start

            playerNameTextIndex++;
        }
        playerNameTextPositionY += distanceBetweenPlayerNameTextsY;
    }
}

void resizeCurrentPlayerInfoTexts()
{
    if(!currentPlayerWhichHasToThrow->isInJail)
    {
        currentPlayerWhichHasToThrow->playerNameText->setCharacterSize(currentPlayerNameTextCharacterSize);
    }
    if(previousPlayer != nullptr)
    {
        previousPlayer->playerNameText->setCharacterSize(playerNameTextCharacterSize);
    }

}

void startGameButtonEventHandler(sf::RenderWindow& window)
{
    if(startGameButton->isMouseOver(window))
    {
        Property* firstProperty = dynamic_cast<Property*>(locations[1]);
        if(firstProperty)
        {
            firstProperty->owner = nullptr; // It should be nullptr by default because it's set in the constructor, but for this particular property it's not
        }
        else
        {
            std::cerr << "First location is not property" << std::endl;
        }
        playerSetupMenu.hideAll();
        inGameScene.showAll();
        buyPropertyButton->visible = false;
        nextButton->visible = false;
        buyHouseButton->visible = false;
        gameOverText->visible = false;
        inGameClockText->visible = false;
        currentState = GameState::InGame;
        createPlayerInfoTexts();
        createPlayerRectangles();
        currentPlayerIndex = 0; // It has to be resetted to 0, in case the game was restarted
        currentPlayerWhichHasToThrow = players[currentPlayerIndex];
        resizeCurrentPlayerInfoTexts();
        startInGameClock();

    }
}

void moveToNextPlayer()
{
    nextButton->visible = false;
    rollDiceButton->visible = true;
    buyPropertyButton->visible = false;
    buyHouseButton->visible = false;
    previousPlayer = currentPlayerWhichHasToThrow;
    currentPlayerIndex++;
    if(currentPlayerIndex >= players.size())
    {
        currentPlayerIndex = 0;
    }
    std::cout << "currentPlayerIndex: " << currentPlayerIndex << std::endl;
    currentPlayerWhichHasToThrow = players[currentPlayerIndex];
    
    if(currentPlayerWhichHasToThrow->isInJail)
    {
        currentPlayerWhichHasToThrow->numberOfTurnsSinceJail++;
        if(currentPlayerWhichHasToThrow->numberOfTurnsSinceJail == numberOfSkippedTurnsWhenPlayerisInJail+1) // Player comes out from jail
        {
            currentPlayerWhichHasToThrow->numberOfTurnsSinceJail = 0;
            currentPlayerWhichHasToThrow->isInJail = false;
            currentPlayerWhichHasToThrow->uiRectangleShapePlayer->setColor(currentPlayerWhichHasToThrow->color);
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

void removeCurrentPlayer()
{
    for(Location* location : currentPlayerWhichHasToThrow->ownedProperties)
    {
        Property* property = dynamic_cast<Property*>(location);

        if(property)
        {
            property->propertyColorSquare->setColor(sf::Color::Black);
            property->owner = nullptr;
        }
    }

    auto it = std::find(players.begin(), players.end(), currentPlayerWhichHasToThrow);

    int indexOfCurrentPlayerWhichHasToThrow;
    if (it != players.end())
    {
        indexOfCurrentPlayerWhichHasToThrow = std::distance(players.begin(), it);

    }

    for(int i=players.size()-1; i > indexOfCurrentPlayerWhichHasToThrow; i--)
    {
        players[i]->playerNameText->setPosition(players[i-1]->playerNameText->getPosition());
        players[i]->playerMoneyAmountText->setPosition(players[i-1]->playerMoneyAmountText->getPosition());
        players[i]->playerProfitAmountText->setPosition(players[i-1]->playerProfitAmountText->getPosition());

    }

    players.erase(it);

    std::vector<UIElement*> elementsToRemove =
    {
        currentPlayerWhichHasToThrow->playerNameText,
        currentPlayerWhichHasToThrow->playerMoneyAmountText,
        currentPlayerWhichHasToThrow->playerProfitAmountText,
        currentPlayerWhichHasToThrow->uiRectangleShapePlayer
    };

    for (UIElement* element : elementsToRemove)
    {
        auto it = std::find(inGameScene.elements.begin(), inGameScene.elements.end(), element);

        if (it != inGameScene.elements.end())
        {
            delete *it;
            inGameScene.elements.erase(it);

        }
    }

    playersInWinningOrder.insert(playersInWinningOrder.begin(), currentPlayerWhichHasToThrow);
    if(players.size() == 1)
    {
        gameOver();
        return;
    }
}

bool hasPlayerLost(Player* player, int amountToPay)
{
    if(player->moneyAmount - amountToPay <=0) // Player has lost
    {
        removeCurrentPlayer();
        return true;
    }
    return false;
}

void rollDiceButtonEventHandler(sf::RenderWindow& window)
{
    if(rollDiceButton->isMouseOver(window))
    {
        auto it = std::find(locations.begin(), locations.end(), currentPlayerWhichHasToThrow->currentLocation);
        if(it != locations.end())
        {
            int rollDiceResult = getRadnomNumberBetweenTwoNumbersInclusive(rollDiceResultMin, rollDiceResultMax);
            rollDiceResultText->setString(std::to_string(rollDiceResult));
            for(Player* player: players)
            {
                player->playerProfitAmountText->setString("");
            }
            if(previousPlayerWhoGotMoneyFromOwningProperty != nullptr)
            {
                previousPlayerWhoGotMoneyFromOwningProperty->playerProfitAmountText->setString("");

            }
            
            int currentLocationIndex = std::distance(locations.begin(), it);
            currentLocationIndex += rollDiceResult;
            if(currentLocationIndex >= locations.size()) // start
            {
                currentLocationIndex -= locations.size();
                if(hasPlayerLost(currentPlayerWhichHasToThrow, amountOfMoneyGotByAPlayerAfterItGoesTroughStart))
                {
                    return;
                }
                currentPlayerWhichHasToThrow->moneyAmount += amountOfMoneyGotByAPlayerAfterItGoesTroughStart;
                currentPlayerWhichHasToThrow->playerProfitAmountText->setString(std::to_string(amountOfMoneyGotByAPlayerAfterItGoesTroughStart));
                currentPlayerWhichHasToThrow->playerMoneyAmountText->setString(std::to_string(currentPlayerWhichHasToThrow->moneyAmount) + "RON");
            }

            sf::Vector2f previousLocationPosition = currentPlayerWhichHasToThrow->currentLocation->position;
            sf::Vector2f currentLocationPosition = locations[currentLocationIndex]->position;
            sf::Vector2f previousUiRectangleShapePlayerPosition = currentPlayerWhichHasToThrow->uiRectangleShapePlayer->getPosition();
            sf::Vector2f uiRectangleShapePlayerPositionOffset = sf::Vector2f(previousUiRectangleShapePlayerPosition.x - previousLocationPosition.x, previousUiRectangleShapePlayerPosition.y - previousLocationPosition.y );
            currentPlayerWhichHasToThrow->uiRectangleShapePlayer->setPosition(sf::Vector2f(currentLocationPosition.x + uiRectangleShapePlayerPositionOffset.x, currentLocationPosition.y + uiRectangleShapePlayerPositionOffset.y));
            currentPlayerWhichHasToThrow->currentLocation = locations[currentLocationIndex];
            nextButton->visible = true;
            rollDiceButton->visible = false;
            currentProperty = dynamic_cast<Property*>(locations[currentLocationIndex]);
            if(currentProperty && currentPlayerWhichHasToThrow->moneyAmount>currentProperty->price && currentProperty->owner == nullptr) // Player can buy property
            {
                buyPropertyButton->visible = true;

            }
            else if(currentProperty && currentProperty->owner != nullptr && currentProperty->owner == currentPlayerWhichHasToThrow) // the property is owned by the player who went there
            { 
                currentRealEstate = dynamic_cast<RealEstate*>(currentProperty);
                if(currentRealEstate) // It's a real estate (houses can be bought)
                {
                    activateBuyHouseButtonIfPlayerCanBuyIt();
                }
                    
            }
            else
            {
                if(currentProperty && currentProperty->owner != nullptr && currentProperty->owner != currentPlayerWhichHasToThrow) // Player has to pay
                {
                    int amountToPay = 0;
                    if(dynamic_cast<TransportProperty*>(currentProperty))
                    {
                        amountToPay = currentProperty->price*percentOfPropertyPriceWhichHasToBePaidWhenPropertyIsVisited/100 * currentProperty->owner->transportPropertyAmount; // If the property is a transport type, the visitor has to pay the usual amount * the number of transport ptoprties owned by the owner
                    }
                    else
                    {
                        currentRealEstate = dynamic_cast<RealEstate*>(currentProperty);
                        if(currentRealEstate)
                        {
                            amountToPay = currentRealEstate->price*percentOfPropertyPriceWhichHasToBePaidWhenPropertyIsVisited/100 + currentRealEstate->houseAmount * currentRealEstate->price*percentOfRealEstatePriceWhichHasToBePaidPerHouseWhenRealEstateIsVisited/100;
                        }
                    }
                    if(hasPlayerLost(currentPlayerWhichHasToThrow, amountToPay))
                    {
                        return;
                    }
                    currentPlayerWhichHasToThrow->moneyAmount -= amountToPay;
                    currentPlayerWhichHasToThrow->playerProfitAmountText->setString("-" + std::to_string(amountToPay));
                    currentPlayerWhichHasToThrow->playerMoneyAmountText->setString(std::to_string(currentPlayerWhichHasToThrow->moneyAmount) + "RON");

                    currentProperty->owner->moneyAmount += amountToPay;
                    currentProperty->owner->playerProfitAmountText->setString("+" + std::to_string(amountToPay));
                    currentProperty->owner->playerMoneyAmountText->setString(std::to_string(currentProperty->owner->moneyAmount) + "RON");
                    previousPlayerWhoGotMoneyFromOwningProperty = currentProperty->owner;

                }
                else if(!currentProperty) // Start, Jail, GoToJail, Tax, Gambling
                {
                    if(dynamic_cast<GoToJailLocation*>(locations[currentLocationIndex])) // Go to jail
                    {
                        currentPlayerWhichHasToThrow->isInJail = true;
                        currentPlayerWhichHasToThrow->uiRectangleShapePlayer->setPosition(sf::Vector2f(locations[20]->position.x + uiRectangleShapePlayerPositionOffset.x, locations[20]->position.y + uiRectangleShapePlayerPositionOffset.y));
                        currentPlayerWhichHasToThrow->currentLocation = locations[20];
                        sf::Color colorOfPlayerInJail = sf::Color(currentPlayerWhichHasToThrow->color.r, currentPlayerWhichHasToThrow->color.g, currentPlayerWhichHasToThrow->color.b, colorOfPlayerInJailAlphaValue);
                        currentPlayerWhichHasToThrow->uiRectangleShapePlayer->setColor(colorOfPlayerInJail);
                        std::cout << "Go to jail" << std::endl;
                    }
                    else if(dynamic_cast<JailLocation*>(locations[currentLocationIndex])) // Visiting jail
                    {
                        std::cout << "Jail" << std::endl;
                    }
                    else if(dynamic_cast<TaxLocation*>(locations[currentLocationIndex])) // Tax
                    {
                        std::cout << "Anaf" << std::endl;
                        for(Player* player : players)
                        {
                            if(hasPlayerLost(player, taxLocationAmount))
                            {
                                return;
                            }
                            player->moneyAmount -= taxLocationAmount;
                            player->playerProfitAmountText->setString("-" + std::to_string(taxLocationAmount));
                            player->playerMoneyAmountText->setString(std::to_string(player->moneyAmount) + "RON");

                        }
                    }
                    else if(dynamic_cast<GamblingLocation*>(locations[currentLocationIndex])) // Gambling
                    {
                        std::cout << "GamblingLocation" << std::endl;
                        int gamblingResult = getRadnomNumberBetweenTwoNumbersInclusive(minimumGamblingAmountProfit, maximumGamblingAmountProfit);
                        if(hasPlayerLost(currentPlayerWhichHasToThrow, gamblingResult))
                        {
                            return;
                        }
                        currentPlayerWhichHasToThrow->moneyAmount += gamblingResult;
                        currentPlayerWhichHasToThrow->playerProfitAmountText->setString(std::to_string(gamblingResult));
                        currentPlayerWhichHasToThrow->playerMoneyAmountText->setString(std::to_string(currentPlayerWhichHasToThrow->moneyAmount) + "RON");

                    }
                }
                
                moveToNextPlayer();
                    
            }
            nextButtonActivatorClock.restart();

        }
    }
}

void buyPropertyButtonEventHandler(sf::RenderWindow& window)
{
    if(buyPropertyButton->isMouseOver(window))
    {
        currentPlayerWhichHasToThrow->ownedProperties.push_back(currentProperty);
        currentPlayerWhichHasToThrow->moneyAmount -= currentProperty->price;
        currentProperty->owner = currentPlayerWhichHasToThrow;
        currentProperty->propertyColorSquare->setColor(currentPlayerWhichHasToThrow->color);
        currentPlayerWhichHasToThrow->playerMoneyAmountText->setString(std::to_string(currentPlayerWhichHasToThrow->moneyAmount) + "RON");
        currentPlayerWhichHasToThrow->playerProfitAmountText->setString("-" + std::to_string(currentProperty->price));
        
        if(dynamic_cast<TransportProperty*>(currentProperty))
        {
            currentPlayerWhichHasToThrow->transportPropertyAmount++;
        }

        moveToNextPlayer();
    }
}

void nextButtonEventHandler(sf::RenderWindow& window)
{
    if(nextButtonActivatorClock.getElapsedTime().asSeconds() < delayAfterWhichNextButtonBecomesPressableAfterBuyPropertyButtonWasPressed) // a small delay has to be added, because otherwise the nextButton is pressed at the same time when the rollDiceButton is pressed
    {
        return;
    }
    if(nextButton->isMouseOver(window))
    {
        moveToNextPlayer();
    }    
}

void moveElementBeforePlayerRectangleShapes(UIElement* uiElement)
{
    auto it = std::find(inGameScene.elements.begin(), inGameScene.elements.end(), uiElement);
    if (it != inGameScene.elements.end())
    {
        auto new_pos = inGameScene.elements.end() - players.size() - 1;
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

void buyHouseButtonEventHandler(sf::RenderWindow& window)
{
    if(buyHouseButton->isMouseOver(window))
    {
        currentRealEstate->houseAmount++;
        int housePrice = currentProperty->price*percentOfRealEstatePriceWhichHasToBePaidToBuyAHouse/100;
        currentPlayerWhichHasToThrow->moneyAmount -= housePrice;
        currentPlayerWhichHasToThrow->playerProfitAmountText->setString("-" + std::to_string(housePrice));
        currentPlayerWhichHasToThrow->playerMoneyAmountText->setString(std::to_string(currentPlayerWhichHasToThrow->moneyAmount) + "RON");        

        if(currentRealEstate->houseAmount == numberOfHousesAfterWhichItsConsideredHotel)
        {
            for(auto it = inGameScene.elements.begin(); it != inGameScene.elements.end();)
            {
                auto sprite = dynamic_cast<UISprite*>(*it);
                if(std::find(currentRealEstate->houseSprites.begin(), currentRealEstate->houseSprites.end(), sprite) != currentRealEstate->houseSprites.end())
                {
                    delete sprite;
                    it = inGameScene.elements.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            currentRealEstate->houseSprites.clear();
            if(!hotelTexture.loadFromFile("Assets/Hotel.png"))
            {
                std::cerr << "Failed to load image" << std::endl;
            }
            UISprite* hotelSprite = new UISprite
            (
                inGameScene,
                &hotelTexture,
                sf::Vector2f
                (
                    currentRealEstate->propertyColorSquare->getPosition().x + (locationSize - hotelSpriteSize)/2,
                    currentRealEstate->propertyColorSquare->getPosition().y + hotelSpritePositionY
                ),
                sf::Vector2f(hotelSpriteSize, hotelSpriteSize)
            );

            moveElementBeforePlayerRectangleShapes(hotelSprite); // It has to be moved before the uiRectangleShapePlayer, otherwise the uiRectangleShapePlayer will be beneath the sprite. The players were the last objects that were added into inGameScene.elements

            inGameSceneUIElementsThatMustBeDeleted.push_back(hotelSprite);
        }
        else
        {
            if(!houseTexture.loadFromFile("Assets/House.png"))
            {
                std::cerr << "Failed to load image" << std::endl;
            }

            UISprite* houseSprite = new UISprite
            (
                inGameScene,
                &houseTexture,
                sf::Vector2f
                (
                    currentRealEstate->propertyColorSquare->getPosition().x + currentRealEstate->houseAmount * (locationSize - 3 * houseSpriteSize )/4 + (currentRealEstate->houseAmount-1) * houseSpriteSize,
                    currentRealEstate->propertyColorSquare->getPosition().y + houseSpritePositionY
                ),
                sf::Vector2f(houseSpriteSize, houseSpriteSize)
            );

            moveElementBeforePlayerRectangleShapes(houseSprite); // It has to be moved before the uiRectangleShapePlayer, otherwise the uiRectangleShapePlayer will be beneath the sprite. The players were the last objects that were added into inGameScene.elements

            inGameSceneUIElementsThatMustBeDeleted.push_back(houseSprite);
            currentRealEstate->houseSprites.push_back(houseSprite);
            
        }
        activateBuyHouseButtonIfPlayerCanBuyIt();

    }
}

void activateBuyHouseButtonIfPlayerCanBuyIt()
{
    int housePrice = currentRealEstate->price*percentOfRealEstatePriceWhichHasToBePaidToBuyAHouse/100;
    if(currentPlayerWhichHasToThrow->moneyAmount > housePrice && currentRealEstate->houseAmount < numberOfHousesAfterWhichItsConsideredHotel)
    {
        buyHouseButton->visible = true;
        
        if(currentRealEstate->houseAmount == numberOfHousesAfterWhichItsConsideredHotel-1)
        {
            buyHouseButton->buttonText.setString("Buy hotel(" + std::to_string(housePrice) + ")");
            buyHouseButton->centerText();
        }
        else
        {
            buyHouseButton->buttonText.setString("Buy house(" + std::to_string(housePrice) + ")");
            buyHouseButton->centerText();
        }
    }
    else
    {
        moveToNextPlayer();
    }
}