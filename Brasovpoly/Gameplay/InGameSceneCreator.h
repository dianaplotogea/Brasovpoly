#ifndef IN_GAME_SCENE_CREATOR_H
#define IN_GAME_SCENE_CREATOR_H

#include "../UI/UIRectangleShape.h"

class InGameSceneCreator
{
public:
    void createInGameScene();
    void createLocationsHorizontalUp();
    void createLocationsVerticalRight();
    void createLocationsHorizontalDown();
    void createLocationsVerticalLeft();
    void createStart();
    void createGoToJailLocation();
    void createJailLocation();
    void createTaxLocation();
    void createGamblingLocation();
    void createInGameSceneButtons();
    void createInGameClockText();
    void createGameOverScreen();
    UIRectangleShape* createPropertySquare(Property* property, sf::Vector2f position);

private:
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
    int goToJailLocationPositionY = 30;

    float taxLocationSpriteWidth = 73;
    float taxLocationSpriteHeight = 103.5;

    float gamblingLocationSpriteSize = 110;

    float rollDiceButtonPositionX = 320;
    float rollDiceButtonPositionY = 592.5;

    float buyPropertyButtonPositionX = 620;
    float buyPropertyButtonPositionY = 592.5;

    float buyHouseButtonPositionX = 920;
    float buyHouseButtonPositionY = 592.5;

    sf::Texture goToJailLocationTexture;
    sf::Texture jailLocationTexture;
    sf::Texture taxLocationTexture;
    sf::Texture gamblingLocationTexture;

    std::vector<std::unique_ptr<sf::Texture>> transportPropertyTextures; 

};

#endif