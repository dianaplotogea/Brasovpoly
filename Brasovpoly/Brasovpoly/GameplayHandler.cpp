#include "GameplayHandler.h"
#include "UI/Button.h"
#include "UI/UIRectangleShape.h"
#include "UI/UIText.h"
#include "InGameSceneCreator.h"
#include "Globals.h"
#include <iostream>
#include <random>
#include <SFML/System/Clock.hpp>

int uiRectangleShapePlayerSize = 30;
int initialPlayerPositionX = 15;
int initialPlayerPositionY = 55;
int distanceBetweenPlayers = 5;
int numberOfColumnsPlayerRectangles = 3;

int numberOfColumnsPlayerInfoTexts = 3;
int playerNameTextCharacterSize = 35;
int currentPlayerNameTextCharacterSize = 58;
int playerNameTextPositionX = 275;
int playerNameTextIntialPositionY = 250;
int distanceBetweenPlayerNameTextsX = 300;
int distanceBetweenPlayerNameTextsY = 175;
int playerProfitAmountTextPositionY = 35;

int initialMoneyAmount = 8000;
int playerMoneyAmountTextPositionY = 68;

int currentPlayerIndex = 0;

float delayAfterWhichNextButtonBecomesPressableAfterBuyPropertyButtonWasPressed = 1;

int percentOfPropertyPriceWhichHasToBePaidWhenPropertyIsVisited = 20;

int rollDiceResultMin = 2;
int rollDiceResultMax = 12;

Player* currentPlayerWhichHasToThrow;
Player* previousPlayer;
Player* previousPlayerWhoGotMoneyFromOwningProperty;

Property* currentProperty;

sf::Clock nextButtonActivatorClock;

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
                sf::Vector2f(locations[0]->position.x + initialPlayerPositionX + i*(distanceBetweenPlayers + uiRectangleShapePlayerSize), playerPositionY),  
                sf::Vector2f(uiRectangleShapePlayerSize, uiRectangleShapePlayerSize),
                players[rectangleIndex]->color
            );
            players[rectangleIndex++]->uiRectangleShapePlayer = uiRectangleShapePlayer;
            inGameSceneUIElementsThatMustBeDeleted.push_back(uiRectangleShapePlayer);
        }
        playerPositionY += distanceBetweenPlayers + uiRectangleShapePlayerSize;
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
    currentPlayerWhichHasToThrow->playerNameText->setCharacterSize(currentPlayerNameTextCharacterSize);
    
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
        playerSetupMenu.hideAll();
        inGameScene.showAll();
        buyPropertyButton->hide();
        nextButton->hide();
        currentState = GameState::InGame;
        createPlayerRectangles();
        createPlayerInfoTexts();
        currentPlayerIndex = 0;
        currentPlayerWhichHasToThrow = players[currentPlayerIndex++];
        resizeCurrentPlayerInfoTexts();

    }
}

void moveToNextPlayer()
{
    nextButton->hide();
    rollDiceButton->show();
    buyPropertyButton->hide();
    previousPlayer = currentPlayerWhichHasToThrow;
    if(currentPlayerIndex == players.size())
    {
        currentPlayerIndex = 0;
    }
    currentPlayerWhichHasToThrow = players[currentPlayerIndex++];
    resizeCurrentPlayerInfoTexts();
}

int getRadnomNumberBetweenTwoNumbersInclusive(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
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
            if(previousPlayer != nullptr)
            {
                previousPlayer->playerProfitAmountText->setString("");
                
            }
            if(previousPlayerWhoGotMoneyFromOwningProperty != nullptr)
            {
                previousPlayerWhoGotMoneyFromOwningProperty->playerProfitAmountText->setString("");
            }
            
            int currentLocationIndex = std::distance(locations.begin(), it);
            currentLocationIndex += rollDiceResult;
            if(currentLocationIndex >= locations.size())
            {
                currentLocationIndex -= locations.size();
            }

            sf::Vector2f previousLocationPosition = currentPlayerWhichHasToThrow->currentLocation->position;
            sf::Vector2f currentLocationPosition = locations[currentLocationIndex]->position;
            sf::Vector2f previousUiRectangleShapePlayerPosition = currentPlayerWhichHasToThrow->uiRectangleShapePlayer->getPosition();
            sf::Vector2f uiRectangleShapePlayerPositionOffset = sf::Vector2f(previousUiRectangleShapePlayerPosition.x - previousLocationPosition.x, previousUiRectangleShapePlayerPosition.y - previousLocationPosition.y );
            currentPlayerWhichHasToThrow->uiRectangleShapePlayer->setPosition(sf::Vector2f(currentLocationPosition.x + uiRectangleShapePlayerPositionOffset.x, currentLocationPosition.y + uiRectangleShapePlayerPositionOffset.y));
            currentPlayerWhichHasToThrow->currentLocation = locations[currentLocationIndex];
            nextButton->show();
            rollDiceButton->hide();
            currentProperty = dynamic_cast<Property*>(locations[currentLocationIndex]);
            if(currentProperty && currentPlayerWhichHasToThrow->moneyAmount>currentProperty->price && currentProperty->owner == nullptr) // Player can buy property
            {
                buyPropertyButton->show();
            }
            else
            {
                if(currentProperty && currentProperty->owner != currentPlayerWhichHasToThrow && currentProperty->owner != nullptr) // Player has to pay
                {
                    int amountToPay = currentProperty->price*percentOfPropertyPriceWhichHasToBePaidWhenPropertyIsVisited/100;

                    if(currentPlayerWhichHasToThrow->moneyAmount - amountToPay <=0)
                    {
                        std::cout << "player lost" << std::endl;
                    }
                    else
                    {
                        std::cout << "player didn't lost" << std::endl;
                        currentPlayerWhichHasToThrow->moneyAmount -= amountToPay;
                        currentPlayerWhichHasToThrow->playerProfitAmountText->setString("-" + std::to_string(amountToPay));
                        currentPlayerWhichHasToThrow->playerMoneyAmountText->setString(std::to_string(currentPlayerWhichHasToThrow->moneyAmount) + "RON");
                    }
                    
                    currentProperty->owner->moneyAmount += amountToPay;
                    currentProperty->owner->playerProfitAmountText->setString("+" + std::to_string(amountToPay));
                    currentProperty->owner->playerMoneyAmountText->setString(std::to_string(currentProperty->owner->moneyAmount) + "RON");
                    previousPlayerWhoGotMoneyFromOwningProperty = currentProperty->owner;
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
        std::cout << "Next button pressed" << std::endl;
        moveToNextPlayer();
    }    
}