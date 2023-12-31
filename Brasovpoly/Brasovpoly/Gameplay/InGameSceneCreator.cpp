#include "GameplayHandler.h"
#include "../UI/Button.h"
#include "../UI/UIRectangleShape.h"
#include "../UI/UIText.h"
#include "../Globals.h"
#include "District.h"
#include "Location.h"
#include "Start.h"
#include "Property.h"
#include <iostream>
#include "InGameSceneCreator.h"

int propertyIndex = 1;
int locationSize = 150;
int locationsPadding = 90;
int locationBorderSize = 5;
int numberOfRowsAndColumnsStart = 5;
int playerIndexTextCharacterSize = 15;
int propertyColorSquareHeight = 50;

int numberOfPropertiesHorizontalUp = 7;
int numberOfPropertiesVerticalLeft = 4;
int numberOfPropertiesHorizontalDown = 8;
int numberOfPropertiesVerticalRight = 4; 

int propertyNameTextPaddingY = 10;
int propertyPriceTextPaddingY = 125;

int rollDiceResultTextPositionX = 1200;
int rollDiceResultTextPositionY = 600;

int rollDiceResultTextCharacterSize = 45;

int gameOverTextCharacterSize = 45;
int gameOverTextPositionY = 100;

int gameOverPlayingTimeTextCharacterSize = 40;

float rollDiceButtonPositionX = 320;
float rollDiceButtonPositionY = 592.5;

float buyPropertyButtonPositionX = 620;
float buyPropertyButtonPositionY = 592.5;

UIRectangleShape* createPropertySquare(sf::Vector2f position)
{
    UIRectangleShape* propertySquare = new UIRectangleShape
    (
        inGameScene,
        position,
        sf::Vector2f(locationSize, locationSize),
        sf::Color::Black
    );
    propertySquare->setBorder(locationBorderSize, sf::Color::White);

    UIRectangleShape* propertyColorSquare = new UIRectangleShape
    (
        inGameScene,
        position,
        sf::Vector2f(locationSize, propertyColorSquareHeight),
        sf::Color::Black
    );
    propertyColorSquares.push_back(propertyColorSquare);

    return propertyColorSquare;
}

void createLocationsHorizontalUp()
{
    for(propertyIndex; propertyIndex<numberOfPropertiesHorizontalUp+1;propertyIndex++)
    {
        Property* property = dynamic_cast<Property*>(locations[propertyIndex]);
        if (property)
        {
            sf::Vector2f propertyPosition = sf::Vector2f(locationsPadding + propertyIndex*locationSize, locationsPadding);
            property->position = propertyPosition;
            property->propertyColorSquare = createPropertySquare(propertyPosition);    

            UIText* propertyNameText = new UIText(inGameScene, &font, playerIndexTextCharacterSize, property->name, property->district.color);
            propertyNameText->setPosition(sf::Vector2f(locationsPadding + propertyIndex*locationSize + (locationSize/2-propertyNameText->getLocalBounds().width/2), locationsPadding + propertyNameTextPaddingY));
            
            UIText* propertyPriceText = new UIText(inGameScene, &font, playerIndexTextCharacterSize, std::to_string(property->price) + "RON", property->district.color);
            propertyPriceText->setPosition(sf::Vector2f(locationsPadding + propertyIndex*locationSize + (locationSize/2-propertyPriceText->getLocalBounds().width/2), locationsPadding + propertyPriceTextPaddingY));
        }
    }
}

void createLocationsVerticalRight()
{
    for(propertyIndex; propertyIndex<numberOfPropertiesHorizontalUp+numberOfPropertiesVerticalLeft+1;propertyIndex++)
    {
        Property* property = dynamic_cast<Property*>(locations[propertyIndex]);
        if (property)
        {
            sf::Vector2f propertyPosition = sf::Vector2f(windowWidth - locationsPadding - locationSize + locationBorderSize, locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-1)*(locationSize + locationBorderSize));
            property->position = propertyPosition;
            property->propertyColorSquare = createPropertySquare(propertyPosition);

            UIText* propertyNameText = new UIText(inGameScene, &font, playerIndexTextCharacterSize, property->name, property->district.color);
            propertyNameText->setPosition(sf::Vector2f(windowWidth - locationsPadding - locationSize + locationBorderSize + (locationSize/2-propertyNameText->getLocalBounds().width/2), locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-1)*(locationSize + locationBorderSize) + propertyNameTextPaddingY));
        
            UIText* propertyPriceText = new UIText(inGameScene, &font, playerIndexTextCharacterSize, std::to_string(property->price) + "RON", property->district.color);
            propertyPriceText->setPosition(sf::Vector2f(windowWidth - locationsPadding - locationSize + locationBorderSize + (locationSize/2-propertyPriceText->getLocalBounds().width/2), locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-1)*(locationSize + locationBorderSize) + propertyPriceTextPaddingY));
        }
    }
}

void createLocationsHorizontalDown()
{
    for(propertyIndex; propertyIndex<numberOfPropertiesHorizontalUp+numberOfPropertiesVerticalLeft+numberOfPropertiesHorizontalDown+1;propertyIndex++)
    {
        Property* property = dynamic_cast<Property*>(locations[(numberOfPropertiesHorizontalUp * 2 + numberOfPropertiesVerticalLeft*2 + numberOfPropertiesHorizontalDown) - propertyIndex + 1]);
        if (property)
        {
            sf::Vector2f propertyPosition = sf::Vector2f(locationsPadding + locationBorderSize + (locationSize) * (propertyIndex-numberOfPropertiesHorizontalUp-numberOfPropertiesVerticalLeft), windowHeight - locationsPadding - locationSize - locationBorderSize*2);
            property->position = propertyPosition;
            property->propertyColorSquare = createPropertySquare(propertyPosition);
        
            UIText* propertyNameText = new UIText(inGameScene, &font, playerIndexTextCharacterSize, property->name, property->district.color);
            propertyNameText->setPosition(sf::Vector2f(locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-numberOfPropertiesVerticalLeft)*locationSize + (locationSize/2-propertyNameText->getLocalBounds().width/2), windowHeight - locationsPadding - locationSize - locationBorderSize*2 + propertyNameTextPaddingY));
            
            UIText* propertyPriceText = new UIText(inGameScene, &font, playerIndexTextCharacterSize, std::to_string(property->price) + "RON", property->district.color);
            propertyPriceText->setPosition(sf::Vector2f(locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-numberOfPropertiesVerticalLeft)*locationSize + (locationSize/2-propertyPriceText->getLocalBounds().width/2), windowHeight - locationsPadding - locationSize - locationBorderSize*2 + propertyPriceTextPaddingY));        
        }
    }
}

void createLocationsVerticalLeft()
{ 
    for(propertyIndex; propertyIndex<numberOfPropertiesHorizontalUp+numberOfPropertiesVerticalLeft+numberOfPropertiesHorizontalDown+numberOfPropertiesVerticalRight+1;propertyIndex++)
    {
        Property* property = dynamic_cast<Property*>(locations[(numberOfPropertiesHorizontalUp*2 + numberOfPropertiesVerticalLeft*2 + numberOfPropertiesHorizontalDown*2 + numberOfPropertiesVerticalRight) - propertyIndex + 1]);
        std::cout<< "propertyIndex: " << (numberOfPropertiesHorizontalUp*2 + numberOfPropertiesVerticalLeft*2 + numberOfPropertiesHorizontalDown*2 + numberOfPropertiesVerticalRight) - propertyIndex << std::endl;
        if (property)
        {
            sf::Vector2f propertyPosition = sf::Vector2f( locationsPadding, locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-numberOfPropertiesVerticalLeft-numberOfPropertiesHorizontalDown)*(locationSize + locationBorderSize));
            property->position = propertyPosition;
            property->propertyColorSquare = createPropertySquare(propertyPosition);
        
            UIText* propertyNameText = new UIText(inGameScene, &font, playerIndexTextCharacterSize, property->name, property->district.color);
            propertyNameText->setPosition(sf::Vector2f(locationsPadding + (locationSize/2-propertyNameText->getLocalBounds().width/2), locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-numberOfPropertiesVerticalLeft-numberOfPropertiesHorizontalDown)*(locationSize + locationBorderSize) + propertyNameTextPaddingY));
            
            UIText* propertyPriceText = new UIText(inGameScene, &font, playerIndexTextCharacterSize, std::to_string(property->price) + "RON", property->district.color);
            propertyPriceText->setPosition(sf::Vector2f(locationsPadding + (locationSize/2-propertyPriceText->getLocalBounds().width/2), locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-numberOfPropertiesVerticalLeft-numberOfPropertiesHorizontalDown)*(locationSize + locationBorderSize) + propertyPriceTextPaddingY));          
        }
    }
}

void createStart()
{
    sf::Vector2f startPosition = sf::Vector2f(locationsPadding, locationsPadding);
    locations[0]->position = startPosition;
    UIRectangleShape* startSquare = new UIRectangleShape
    (
        inGameScene,
        startPosition,
        sf::Vector2f(locationSize, locationSize),
        sf::Color::Black
    );
    startSquare->setBorder(locationBorderSize, sf::Color::White);

    float startSquareSmallSize = locationSize/numberOfRowsAndColumnsStart;
    for(int i=1;i<numberOfRowsAndColumnsStart+1;i++)
    {
        for(int j=1;j<numberOfRowsAndColumnsStart+1;j++)
        {
            UIRectangleShape* startSquareSmall = new UIRectangleShape
            (
                inGameScene,
                sf::Vector2f(locationsPadding + (i-1)*startSquareSmallSize, locationsPadding + (j-1)*startSquareSmallSize),
                sf::Vector2f(startSquareSmallSize, startSquareSmallSize),
                (i+j) %2 == 0 ? sf::Color::White : sf::Color::Black
            );
            
        }
    }
}

void createInGameSceneButtons()
{
    rollDiceButton = new Button(inGameScene, rollDiceButtonPositionX, rollDiceButtonPositionY, buttonWidth, buttonHeight, &font, "Roll Dice", buttonColor, buttonBorderThickness, buttonBorderColor);
    outlineColorHoverButtons.push_back(rollDiceButton);
    buyPropertyButton = new Button(inGameScene, buyPropertyButtonPositionX, buyPropertyButtonPositionY, buttonWidth, buttonHeight, &font, "Buy property", buttonColor, buttonBorderThickness, buttonBorderColor);
    outlineColorHoverButtons.push_back(buyPropertyButton);
    nextButton = new Button(inGameScene, rollDiceButtonPositionX, rollDiceButtonPositionY, buttonWidth, buttonHeight, &font, "Next", buttonColor, buttonBorderThickness, buttonBorderColor);
    outlineColorHoverButtons.push_back(nextButton);
    
    rollDiceResultText = new UIText(inGameScene, &font, rollDiceResultTextCharacterSize, "" );
    rollDiceResultText->setPosition(sf::Vector2f(rollDiceResultTextPositionX, rollDiceResultTextPositionY));
}

void createInGameClockText()
{
    inGameClockText = new UIText(inGameScene);
    
}

void createGameOverScreen()
{
    gameOverText = new UIText(inGameScene, &font, gameOverTextCharacterSize, "Game Over");
    gameOverText->setPosition(sf::Vector2f(windowWidth/2-gameOverText->getLocalBounds().width/2, gameOverTextPositionY));

    gameOverPlayingTimeText = new UIText(inGameScene, &font, gameOverPlayingTimeTextCharacterSize);
}

void createInGameScene()
{
    createLocationsHorizontalUp();
    createLocationsVerticalRight();
    createLocationsHorizontalDown();
    createLocationsVerticalLeft();
    createStart();
    createInGameSceneButtons();
    createInGameClockText();
    createGameOverScreen();

    inGameScene.hideAll();
}