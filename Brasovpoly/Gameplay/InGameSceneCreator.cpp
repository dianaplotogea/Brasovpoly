#include "GameplayHandler.h"
#include "../UI/Button.h"
#include "../UI/UIRectangleShape.h"
#include "../UI/UIText.h"
#include "../Globals.h"
#include "Location.h"
#include "Start.h"
#include "Property.h"
#include "TransportProperty.h"
#include "GoToJailLocation.h"
#include <iostream>
#include "InGameSceneCreator.h"

int propertyIndex = 1;
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

int transportPropertyTextureSize = 75;

int goToJailLocationSize = 90;
int goToJailPositionY = 30;

float rollDiceButtonPositionX = 320;
float rollDiceButtonPositionY = 592.5;

float buyPropertyButtonPositionX = 620;
float buyPropertyButtonPositionY = 592.5;

float buyHouseButtonPositionX = 920;
float buyHouseButtonPositionY = 592.5;

sf::Texture goToJailLocationTexture;
sf::Texture jailLocationTexture;

std::vector<std::unique_ptr<sf::Texture>> transportPropertyTextures; 

UIRectangleShape* createPropertySquare(Property* property, sf::Vector2f position)
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

    TransportProperty* transportProperty = dynamic_cast<TransportProperty*>(property);
    if(transportProperty)
    {   
        std::unique_ptr<sf::Texture> newTexture(new sf::Texture()); // It has to be made using unique_ptr because otherwise the same texture will be used for each UISprite
        if(!newTexture->loadFromFile("Assets/" + transportProperty->imageFileName))
        {   
            std::cerr << "Failed to load image" << std::endl;
        }
        else
        {
            UISprite* uiSprite = new UISprite(inGameScene, newTexture.get(), sf::Vector2f(position.x + (locationSize - transportPropertyTextureSize)/2, position.y + (locationSize - transportPropertyTextureSize)/2), sf::Vector2f(transportPropertyTextureSize, transportPropertyTextureSize));
            transportPropertyTextures.push_back(std::move(newTexture)); // Transfer ownership of texture to container
            std::cout << "transport created" << std::endl;
        }
    }   

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
            property->propertyColorSquare = createPropertySquare(property, propertyPosition);    

            UIText* propertyNameText = new UIText(inGameScene, &font, playerIndexTextCharacterSize, property->name);
            propertyNameText->setPosition(sf::Vector2f(locationsPadding + propertyIndex*locationSize + (locationSize/2-propertyNameText->getLocalBounds().width/2), locationsPadding + propertyNameTextPaddingY));
            
            UIText* propertyPriceText = new UIText(inGameScene, &font, playerIndexTextCharacterSize, std::to_string(property->price) + "RON");
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
            property->propertyColorSquare = createPropertySquare(property, propertyPosition);

            UIText* propertyNameText = new UIText(inGameScene, &font, playerIndexTextCharacterSize, property->name);
            propertyNameText->setPosition(sf::Vector2f(windowWidth - locationsPadding - locationSize + locationBorderSize + (locationSize/2-propertyNameText->getLocalBounds().width/2), locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-1)*(locationSize + locationBorderSize) + propertyNameTextPaddingY));
        
            UIText* propertyPriceText = new UIText(inGameScene, &font, playerIndexTextCharacterSize, std::to_string(property->price) + "RON");
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
            property->propertyColorSquare = createPropertySquare(property, propertyPosition);
        
            UIText* propertyNameText = new UIText(inGameScene, &font, playerIndexTextCharacterSize, property->name);
            propertyNameText->setPosition(sf::Vector2f(locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-numberOfPropertiesVerticalLeft)*locationSize + (locationSize/2-propertyNameText->getLocalBounds().width/2), windowHeight - locationsPadding - locationSize - locationBorderSize*2 + propertyNameTextPaddingY));
            
            UIText* propertyPriceText = new UIText(inGameScene, &font, playerIndexTextCharacterSize, std::to_string(property->price) + "RON");
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
            property->propertyColorSquare = createPropertySquare(property, propertyPosition);
        
            UIText* propertyNameText = new UIText(inGameScene, &font, playerIndexTextCharacterSize, property->name);
            propertyNameText->setPosition(sf::Vector2f(locationsPadding + (locationSize/2-propertyNameText->getLocalBounds().width/2), locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-numberOfPropertiesVerticalLeft-numberOfPropertiesHorizontalDown)*(locationSize + locationBorderSize) + propertyNameTextPaddingY));
            
            UIText* propertyPriceText = new UIText(inGameScene, &font, playerIndexTextCharacterSize, std::to_string(property->price) + "RON");
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

void createGoToJailLocation()
{
    sf::Vector2f goToJailLocationPosition = sf::Vector2f(windowWidth - locationsPadding - locationSize + buttonBorderThickness*1.75, locationsPadding); 
    locations[8]->position = goToJailLocationPosition;
    UIRectangleShape* goToJailLocationSquare = new UIRectangleShape
    (
        inGameScene,
        goToJailLocationPosition,
        sf::Vector2f(locationSize, locationSize),
        sf::Color::Black
    );
    goToJailLocationSquare->setBorder(locationBorderSize, sf::Color::White);
    if(!goToJailLocationTexture.loadFromFile("Assets/GoToJail.png"))
    {
        std::cerr << "Failed to load image" << std::endl;
    }
    UISprite* goToJailLocationSprite = new UISprite
    (
        inGameScene,
        &goToJailLocationTexture,
        sf::Vector2f(goToJailLocationPosition.x + (locationSize - goToJailLocationSize)/2,
        goToJailLocationPosition.y + goToJailPositionY),
        sf::Vector2f(goToJailLocationSize, goToJailLocationSize)
    );
    UIText* goToJailLocationText = new UIText
    (
        inGameScene,
        &font,
        playerIndexTextCharacterSize,
        "Du-te-n Codlea!"
    );
    goToJailLocationText->setPosition(sf::Vector2f(goToJailLocationPosition.x + (locationSize - goToJailLocationText->getLocalBounds().width)/2 , locationsPadding + propertyNameTextPaddingY));
    
}

void createJailLocation()
{
    sf::Vector2f jailLocationPosition = sf::Vector2f(locationsPadding, locationsPadding + 4*locationSize + 6.75*buttonBorderThickness);
    locations[20]->position = jailLocationPosition;
    UIRectangleShape* jailLocationSquare = new UIRectangleShape
    (
        inGameScene,
        jailLocationPosition,
        sf::Vector2f(locationSize, locationSize),
        sf::Color::Black
    );
    if(!jailLocationTexture.loadFromFile("Assets/Jail.png"))
    {
        std::cerr << "Failed to load image" << std::endl;
    }
    UISprite* jailLocationSprite = new UISprite
    (
        inGameScene,
        &jailLocationTexture,
        sf::Vector2f(jailLocationPosition.x + (locationSize - goToJailLocationSize)/2,
        jailLocationPosition.y + goToJailPositionY),
        sf::Vector2f(goToJailLocationSize, goToJailLocationSize)
    );
    jailLocationSquare->setBorder(locationBorderSize, sf::Color::White);
    UIText* jailLocationText = new UIText
    (
        inGameScene,
        &font,
        playerIndexTextCharacterSize,
        "Codlea"
    );
    jailLocationText->setPosition(sf::Vector2f(jailLocationPosition.x + (locationSize - jailLocationText->getLocalBounds().width)/2 , jailLocationPosition.y + propertyNameTextPaddingY));
}

void createInGameSceneButtons()
{
    rollDiceButton = new Button(inGameScene, rollDiceButtonPositionX, rollDiceButtonPositionY, buttonWidth, buttonHeight, &font, "Roll Dice", buttonColor, buttonBorderThickness, buttonBorderColor);
    outlineColorHoverButtons.push_back(rollDiceButton);
    buyPropertyButton = new Button(inGameScene, buyPropertyButtonPositionX, buyPropertyButtonPositionY, buttonWidth, buttonHeight, &font, "Buy property", buttonColor, buttonBorderThickness, buttonBorderColor);
    outlineColorHoverButtons.push_back(buyPropertyButton);
    nextButton = new Button(inGameScene, rollDiceButtonPositionX, rollDiceButtonPositionY, buttonWidth, buttonHeight, &font, "Next", buttonColor, buttonBorderThickness, buttonBorderColor);
    outlineColorHoverButtons.push_back(nextButton);
    buyHouseButton = new Button(inGameScene, buyHouseButtonPositionX, buyHouseButtonPositionY, buttonWidth, buttonHeight, &font, "Buy home", buttonColor, buttonBorderThickness, buttonBorderColor);
    outlineColorHoverButtons.push_back(buyHouseButton);

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
    createGoToJailLocation();
    createJailLocation();
    createInGameSceneButtons();
    createInGameClockText();
    createGameOverScreen();

    inGameScene.hideAll();
}