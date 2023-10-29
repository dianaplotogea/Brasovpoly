#ifndef GAMEPLAY_HANDLER_H
#define GAMEPLAY_HANDLER_H

#include <SFML/Graphics.hpp>
#include "RealEstate.h"
#include "../UI/UIRectangleShape.h"
#include "../UI/Button.h"
#include "../UI/UIText.h"
#include "../UI/UISprite.h"

class GameplayHandler
{
    int percentOfPropertyPriceWhichHasToBePaidWhenPropertyIsVisited = 20;
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

    int initialMoneyAmount = 10000;
    int playerMoneyAmountTextPositionY = 68;

    int currentPlayerIndex = 0;

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

public:
    int getPercentOfPropertyPriceWhichHasToBePaidWhenPropertyIsVisited();
    void createPlayerRectangles();
    void createPlayerInfoTexts();
    void resizeCurrentPlayerInfoTexts();
    void moveToNextPlayer();
    void removeCurrentPlayer();
    bool hasPlayerLost(Player* player, int amountToPay);
    void startGameButtonEventHandler(sf::RenderWindow& window);
    void rollDiceButtonEventHandler(sf::RenderWindow& window);
    void buyPropertyButtonEventHandler(sf::RenderWindow& window);
    void nextButtonEventHandler(sf::RenderWindow& window);
    void buyHouseButtonEventHandler(sf::RenderWindow& window);
    void activateBuyHouseButtonIfPlayerCanBuyIt();
    
};

#endif