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
int initialPlayerPositionY = 40;
int distanceBetweenPlayers = 15;
int numberOfColumnsPlayerRectangles = 3;

int numberOfColumnsPlayerInfoTexts = 3;
int playerNameTextCharacterSize = 35;
int currentPlayerNameTextCharacterSize = 45;
int playerNameTextPositionX = 300;
int playerNameTextIntialPositionY = 300;
int distanceBetweenPlayerNameTextsX = 250;
int distanceBetweenPlayerNameTextsY = 125;

int initialMoneyAmount = 5000;
int playerMoneyAmountTextPositionY = 50;

int currentPlayerIndex = 0;

Player* currentPlayerWhichHasToThrow;
Player* previousPlayer;

Property* currentProperty;

sf::Clock myGameClock;

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
            UIText* playerNameText = new UIText(inGameScene, &font, playerNameTextCharacterSize, players[i]->name, players[playerNameTextIndex]->color);
            playerNameText->setPosition(sf::Vector2f(playerNameTextPositionX + i * distanceBetweenPlayerNameTextsX, playerNameTextPositionY));
            inGameSceneUIElementsThatMustBeDeleted.push_back(playerNameText);

            UIText* playerMoneyAmountText = new UIText(inGameScene, &font, playerNameTextCharacterSize, std::to_string(initialMoneyAmount) + "RON", players[playerNameTextIndex]->color);
            playerMoneyAmountText->setPosition(sf::Vector2f(playerNameTextPositionX + i * distanceBetweenPlayerNameTextsX, playerNameTextPositionY + playerMoneyAmountTextPositionY));
            inGameSceneUIElementsThatMustBeDeleted.push_back(playerMoneyAmountText);

            players[playerNameTextIndex]->moneyAmount = initialMoneyAmount;
            players[playerNameTextIndex]->playerNameText = playerNameText;
            players[playerNameTextIndex]->playerMoneyAmountText = playerMoneyAmountText;
            players[playerNameTextIndex]->currentLocation = locations[0]; // Start

            playerNameTextIndex++;
        }
        playerNameTextPositionY += distanceBetweenPlayerNameTextsY;
    }
}

void resizeCurrentPlayerInfoTexts()
{
    currentPlayerWhichHasToThrow->playerNameText->setCharacterSize(currentPlayerNameTextCharacterSize);
    currentPlayerWhichHasToThrow->playerMoneyAmountText->setCharacterSize(currentPlayerNameTextCharacterSize);

    if(previousPlayer != nullptr)
    {
        previousPlayer->playerNameText->setCharacterSize(playerNameTextCharacterSize);
        previousPlayer->playerMoneyAmountText->setCharacterSize(playerNameTextCharacterSize);
    }

}

void startGameButtonEventHandler(sf::RenderWindow& window)
{
    if(startGameButton->isMouseOver(window))
    {
        std::cout << "startGame" << std::endl;
        playerSetupMenu.hideAll();
        inGameScene.showAll();
        buyPropertyButton->hide();
        nextButton->hide();
        currentState = GameState::InGame;
        createPlayerRectangles();
        createPlayerInfoTexts();
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
        int rollDiceResult = getRadnomNumberBetweenTwoNumbersInclusive(2, 12);
        auto it = std::find(locations.begin(), locations.end(), currentPlayerWhichHasToThrow->currentLocation);
        if(it != locations.end())
        {
            int currentLocationIndex = std::distance(locations.begin(), it);
            std::cout << "Player is at " << currentLocationIndex << std::endl;
            std::cout << "Roll dice: " << rollDiceResult << std::endl;
            currentLocationIndex += rollDiceResult;
            if(currentLocationIndex >= locations.size())
            {
                currentLocationIndex -= locations.size();
            }

            sf::Vector2f previousLocationPosition = currentPlayerWhichHasToThrow->currentLocation->position;
            sf::Vector2f currentLocationPosition = locations[currentLocationIndex]->position;
            sf::Vector2f previousUiRectangleShapePlayerPosition = currentPlayerWhichHasToThrow->uiRectangleShapePlayer->getPosition();
            sf::Vector2f uiRectangleShapePlayerPositionOffset = sf::Vector2f(previousUiRectangleShapePlayerPosition.x - previousLocationPosition.x, previousUiRectangleShapePlayerPosition.y - previousLocationPosition.y );
            std::cout << "uiRectangleShapePlayerPositionOffset.x " << uiRectangleShapePlayerPositionOffset.x << std::endl;
            std::cout << "uiRectangleShapePlayerPositionOffset.y " << uiRectangleShapePlayerPositionOffset.y << std::endl;
            currentPlayerWhichHasToThrow->uiRectangleShapePlayer->setPosition(sf::Vector2f(currentLocationPosition.x + uiRectangleShapePlayerPositionOffset.x, currentLocationPosition.y + uiRectangleShapePlayerPositionOffset.y));
            std::cout << "player moved to " << currentLocationIndex << std::endl;
            currentPlayerWhichHasToThrow->currentLocation = locations[currentLocationIndex];
            nextButton->show();
            rollDiceButton->hide();
            currentProperty = dynamic_cast<Property*>(locations[currentLocationIndex]);
            if(currentProperty && currentPlayerWhichHasToThrow->moneyAmount>currentProperty->price && currentProperty->owner == nullptr)
            {
                std::cout << "Player can buy property" << std::endl;
                buyPropertyButton->show();
            }
            else
            {
                if(currentProperty && currentProperty->owner != currentPlayerWhichHasToThrow && currentProperty->owner != nullptr)
                {
                    currentPlayerWhichHasToThrow->moneyAmount -= currentProperty->price/100;
                    currentPlayerWhichHasToThrow->playerMoneyAmountText->setString(std::to_string(currentPlayerWhichHasToThrow->moneyAmount) + "RON");
                    std::cout << "Player had to pay because" << currentProperty->name << " is owned by " << currentProperty->owner->name  << std::endl;
                }
                moveToNextPlayer();
            }
            myGameClock.restart();
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
        currentProperty->propertySquare->setColor(currentPlayerWhichHasToThrow->color);
        currentPlayerWhichHasToThrow->playerMoneyAmountText->setString(std::to_string(currentPlayerWhichHasToThrow->moneyAmount) + "RON");
        moveToNextPlayer();
    }
}

void nextButtonEventHandler(sf::RenderWindow& window)
{
    if(myGameClock.getElapsedTime().asSeconds() < 1.0) // a small delay has to be added, because otherwise the nextButton is pressed at the same time when the rollDiceButton is pressed
    {
        return;
    }
    if(nextButton->isMouseOver(window))
    {
        std::cout << "Next button pressed" << std::endl;
        moveToNextPlayer();
    }    
}