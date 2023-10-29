#include "GameplayHandler.h"
#include "../UI/Button.h"
#include "../UI/UIText.h"
#include "../Globals.h"
#include "Location.h"
#include "Start.h"
#include "Property.h"
#include "TransportProperty.h"
#include "GoToJailLocation.h"
#include <iostream>
#include "InGameSceneCreator.h"



UIRectangleShape* InGameSceneCreator::createPropertySquare(Property* property, sf::Vector2f position)
{
    UIRectangleShape* propertySquare = new UIRectangleShape
    (
        globals.getInGameScene(),
        position,
        sf::Vector2f(Globals::locationSize, Globals::locationSize),
        sf::Color::Black
    );
    propertySquare->setBorder(locationBorderSize, sf::Color::White);

    UIRectangleShape* propertyColorSquare = new UIRectangleShape
    (
        globals.getInGameScene(),
        position,
        sf::Vector2f(Globals::locationSize, propertyColorSquareHeight),
        sf::Color::Black
    );
    globals.getPropertyColorSquares().push_back(propertyColorSquare);

    TransportProperty* transportProperty = dynamic_cast<TransportProperty*>(property);
    if(transportProperty)
    {   
        std::unique_ptr<sf::Texture> newTexture(new sf::Texture()); // It has to be made using unique_ptr because otherwise the same texture will be used for each UISprite
        if(!newTexture->loadFromFile("Assets/" + transportProperty->getImageFileName()))
        {   
            std::cerr << "Failed to load image" << std::endl;
        }
        else
        {
            UISprite* uiSprite = new UISprite(globals.getInGameScene(), newTexture.get(), sf::Vector2f(position.x + (Globals::locationSize - transportPropertyTextureSize)/2, position.y + (Globals::locationSize - transportPropertyTextureSize)/2), sf::Vector2f(transportPropertyTextureSize, transportPropertyTextureSize));
            transportPropertyTextures.push_back(std::move(newTexture)); // Transfer ownership of texture to container
            std::cout << "transport created" << std::endl;
        }
    }   

    return propertyColorSquare;
}

void InGameSceneCreator::createLocationsHorizontalUp()
{
    for(propertyIndex; propertyIndex<numberOfPropertiesHorizontalUp+1;propertyIndex++)
    {
        Property* property = dynamic_cast<Property*>(globals.getLocations()[propertyIndex]);
        if (property)
        {
            sf::Vector2f propertyPosition = sf::Vector2f(locationsPadding + propertyIndex*Globals::locationSize, locationsPadding);
            property->position = propertyPosition;
            property->setPropertyColorSquare(createPropertySquare(property, propertyPosition));    

            UIText* propertyNameText = new UIText(globals.getInGameScene(), globals.getGlobalFont(), playerIndexTextCharacterSize, property->getName());
            propertyNameText->setPosition(sf::Vector2f(locationsPadding + propertyIndex*Globals::locationSize + (Globals::locationSize/2-propertyNameText->getLocalBounds().width/2), locationsPadding + propertyNameTextPaddingY));
            
            UIText* propertyPriceText = new UIText(globals.getInGameScene(), globals.getGlobalFont(), playerIndexTextCharacterSize, std::to_string(property->getPrice()) + "RON");
            propertyPriceText->setPosition(sf::Vector2f(locationsPadding + propertyIndex*Globals::locationSize + (Globals::locationSize/2-propertyPriceText->getLocalBounds().width/2), locationsPadding + propertyPriceTextPaddingY));
        
        }
        
    }
}

void InGameSceneCreator::createLocationsVerticalRight()
{
    for(propertyIndex; propertyIndex<numberOfPropertiesHorizontalUp+numberOfPropertiesVerticalLeft+1;propertyIndex++)
    {
        Property* property = dynamic_cast<Property*>(globals.getLocations()[propertyIndex]);
        if (property)
        {
            sf::Vector2f propertyPosition = sf::Vector2f(Globals::windowWidth - locationsPadding - Globals::locationSize + locationBorderSize, locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-1)*(globals.locationSize + locationBorderSize));
            property->position = propertyPosition;
            property->setPropertyColorSquare(createPropertySquare(property, propertyPosition));

            UIText* propertyNameText = new UIText(globals.getInGameScene(), globals.getGlobalFont(), playerIndexTextCharacterSize, property->getName());
            propertyNameText->setPosition(sf::Vector2f(Globals::windowWidth - locationsPadding - Globals::locationSize + locationBorderSize + (Globals::locationSize/2-propertyNameText->getLocalBounds().width/2), locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-1)*(Globals::locationSize + locationBorderSize) + propertyNameTextPaddingY));
        
            UIText* propertyPriceText = new UIText(globals.getInGameScene(), globals.getGlobalFont(), playerIndexTextCharacterSize, std::to_string(property->getPrice()) + "RON");
            propertyPriceText->setPosition(sf::Vector2f(Globals::windowWidth - locationsPadding - Globals::locationSize + locationBorderSize + (Globals::locationSize/2-propertyPriceText->getLocalBounds().width/2), locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-1)*(Globals::locationSize + locationBorderSize) + propertyPriceTextPaddingY));
        }
    }
}

void InGameSceneCreator::createLocationsHorizontalDown()
{
    for(propertyIndex; propertyIndex<numberOfPropertiesHorizontalUp+numberOfPropertiesVerticalLeft+numberOfPropertiesHorizontalDown+1;propertyIndex++)
    {
        Property* property = dynamic_cast<Property*>(globals.getLocations()[(numberOfPropertiesHorizontalUp * 2 + numberOfPropertiesVerticalLeft*2 + numberOfPropertiesHorizontalDown) - propertyIndex + 1]);
        if (property)
        {
            sf::Vector2f propertyPosition = sf::Vector2f(locationsPadding + locationBorderSize + (Globals::locationSize) * (propertyIndex-numberOfPropertiesHorizontalUp-numberOfPropertiesVerticalLeft), Globals::windowHeight - locationsPadding - globals.locationSize - locationBorderSize*2);
            property->position = propertyPosition;
            property->setPropertyColorSquare(createPropertySquare(property, propertyPosition));
        
            UIText* propertyNameText = new UIText(globals.getInGameScene(), globals.getGlobalFont(), playerIndexTextCharacterSize, property->getName());
            propertyNameText->setPosition(sf::Vector2f(locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-numberOfPropertiesVerticalLeft)*Globals::locationSize + (Globals::locationSize/2-propertyNameText->getLocalBounds().width/2), Globals::windowHeight - locationsPadding - Globals::locationSize - locationBorderSize*2 + propertyNameTextPaddingY));
            
            UIText* propertyPriceText = new UIText(globals.getInGameScene(), globals.getGlobalFont(), playerIndexTextCharacterSize, std::to_string(property->getPrice()) + "RON");
            propertyPriceText->setPosition(sf::Vector2f(locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-numberOfPropertiesVerticalLeft)*Globals::locationSize + (Globals::locationSize/2-propertyPriceText->getLocalBounds().width/2), Globals::windowHeight - locationsPadding - Globals::locationSize - locationBorderSize*2 + propertyPriceTextPaddingY));        
        }
    }
}

void InGameSceneCreator::createLocationsVerticalLeft()
{ 
    for(propertyIndex; propertyIndex<numberOfPropertiesHorizontalUp+numberOfPropertiesVerticalLeft+numberOfPropertiesHorizontalDown+numberOfPropertiesVerticalRight+1;propertyIndex++)
    {
        Property* property = dynamic_cast<Property*>(globals.getLocations()[(numberOfPropertiesHorizontalUp*2 + numberOfPropertiesVerticalLeft*2 + numberOfPropertiesHorizontalDown*2 + numberOfPropertiesVerticalRight) - propertyIndex + 1]);
        std::cout<< "propertyIndex: " << (numberOfPropertiesHorizontalUp*2 + numberOfPropertiesVerticalLeft*2 + numberOfPropertiesHorizontalDown*2 + numberOfPropertiesVerticalRight) - propertyIndex << std::endl;
        if (property)
        {
            sf::Vector2f propertyPosition = sf::Vector2f( locationsPadding, locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-numberOfPropertiesVerticalLeft-numberOfPropertiesHorizontalDown)*(Globals::locationSize + locationBorderSize));
            property->position = propertyPosition;
            property->setPropertyColorSquare(createPropertySquare(property, propertyPosition));
        
            UIText* propertyNameText = new UIText(globals.getInGameScene(), globals.getGlobalFont(), playerIndexTextCharacterSize, property->getName());
            propertyNameText->setPosition(sf::Vector2f(locationsPadding + (Globals::locationSize/2-propertyNameText->getLocalBounds().width/2), locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-numberOfPropertiesVerticalLeft-numberOfPropertiesHorizontalDown)*(Globals::locationSize + locationBorderSize) + propertyNameTextPaddingY));
            
            UIText* propertyPriceText = new UIText(globals.getInGameScene(), globals.getGlobalFont(), playerIndexTextCharacterSize, std::to_string(property->getPrice()) + "RON");
            propertyPriceText->setPosition(sf::Vector2f(locationsPadding + (Globals::locationSize/2-propertyPriceText->getLocalBounds().width/2), locationsPadding + (propertyIndex-numberOfPropertiesHorizontalUp-numberOfPropertiesVerticalLeft-numberOfPropertiesHorizontalDown)*(Globals::locationSize + locationBorderSize) + propertyPriceTextPaddingY));          
        }
    }
}

void InGameSceneCreator::createStart()
{
    sf::Vector2f startPosition = sf::Vector2f(locationsPadding, locationsPadding);
    globals.getLocations()[0]->position = startPosition;
    UIRectangleShape* startSquare = new UIRectangleShape
    (
        globals.getInGameScene(),
        startPosition,
        sf::Vector2f(Globals::locationSize, Globals::locationSize),
        sf::Color::Black
    );
    startSquare->setBorder(locationBorderSize, sf::Color::White);

    float startSquareSmallSize = Globals::locationSize/numberOfRowsAndColumnsStart;
    for(int i=1;i<numberOfRowsAndColumnsStart+1;i++)
    {
        for(int j=1;j<numberOfRowsAndColumnsStart+1;j++)
        {
            UIRectangleShape* startSquareSmall = new UIRectangleShape
            (
                globals.getInGameScene(),
                sf::Vector2f(locationsPadding + (i-1)*startSquareSmallSize, locationsPadding + (j-1)*startSquareSmallSize),
                sf::Vector2f(startSquareSmallSize, startSquareSmallSize),
                (i+j) %2 == 0 ? sf::Color::White : sf::Color::Black
            );
            
        }
    }
}

void InGameSceneCreator::createGoToJailLocation()
{
    sf::Vector2f goToJailLocationPosition = sf::Vector2f(Globals::windowWidth - locationsPadding - Globals::locationSize + Globals::buttonBorderThickness*1.75, locationsPadding); 
    globals.getLocations()[8]->position = goToJailLocationPosition;
    UIRectangleShape* goToJailLocationSquare = new UIRectangleShape
    (
        globals.getInGameScene(),
        goToJailLocationPosition,
        sf::Vector2f(Globals::locationSize, Globals::locationSize),
        sf::Color::Black
    );
    goToJailLocationSquare->setBorder(locationBorderSize, sf::Color::White);
    if(!goToJailLocationTexture.loadFromFile("Assets/GoToJail.png"))
    {
        std::cerr << "Failed to load image" << std::endl;
    }
    UISprite* goToJailLocationSprite = new UISprite
    (
        globals.getInGameScene(),
        &goToJailLocationTexture,
        sf::Vector2f(goToJailLocationPosition.x + (Globals::locationSize - goToJailLocationSize)/2,
        goToJailLocationPosition.y + goToJailLocationPositionY),
        sf::Vector2f(goToJailLocationSize, goToJailLocationSize)
    );
    UIText* goToJailLocationText = new UIText
    (
        globals.getInGameScene(),
        globals.getGlobalFont(),
        playerIndexTextCharacterSize,
        "Du-te-n Codlea!"
    );
    goToJailLocationText->setPosition(sf::Vector2f(goToJailLocationPosition.x + (Globals::locationSize - goToJailLocationText->getLocalBounds().width)/2 , locationsPadding + propertyNameTextPaddingY));
    
}

void InGameSceneCreator::createJailLocation()
{
    sf::Vector2f jailLocationPosition = sf::Vector2f(locationsPadding, locationsPadding + 4*Globals::locationSize + 6.75*Globals::buttonBorderThickness);
    globals.getLocations()[20]->position = jailLocationPosition;
    UIRectangleShape* jailLocationSquare = new UIRectangleShape
    (
        globals.getInGameScene(),
        jailLocationPosition,
        sf::Vector2f(Globals::locationSize, Globals::locationSize),
        sf::Color::Black
    );
    jailLocationSquare->setBorder(locationBorderSize, sf::Color::White);
    if(!jailLocationTexture.loadFromFile("Assets/Jail.png"))
    {
        std::cerr << "Failed to load image" << std::endl;
    }
    UISprite* jailLocationSprite = new UISprite
    (
        globals.getInGameScene(),
        &jailLocationTexture,
        sf::Vector2f(jailLocationPosition.x + (Globals::locationSize - goToJailLocationSize)/2,
        jailLocationPosition.y + goToJailLocationPositionY),
        sf::Vector2f(goToJailLocationSize, goToJailLocationSize)
    );
    
    UIText* jailLocationText = new UIText
    (
        globals.getInGameScene(),
        globals.getGlobalFont(),
        playerIndexTextCharacterSize,
        "Codlea"
    );
    jailLocationText->setPosition(sf::Vector2f(jailLocationPosition.x + (Globals::locationSize - jailLocationText->getLocalBounds().width)/2 , jailLocationPosition.y + propertyNameTextPaddingY));
}

void InGameSceneCreator::createTaxLocation()
{
    sf::Vector2f taxLocationPosition = sf::Vector2f(locationsPadding + 6*Globals::locationSize + Globals::buttonBorderThickness, locationsPadding + 4*Globals::locationSize + 6.75*Globals::buttonBorderThickness);
    globals.getLocations()[14]->position = taxLocationPosition;
    UIRectangleShape* taxLocationSquare = new UIRectangleShape
    (
        globals.getInGameScene(),
        taxLocationPosition,
        sf::Vector2f(Globals::locationSize, Globals::locationSize),
        sf::Color::Black
    );
    taxLocationSquare->setBorder(locationBorderSize, sf::Color::White);
    if(!taxLocationTexture.loadFromFile("Assets/ANAF.png"))
    {
        std::cerr << "Failed to load image" << std::endl;
    }
    UISprite* taxLocationSprite = new UISprite
    (
        globals.getInGameScene(),
        &taxLocationTexture,
        sf::Vector2f(taxLocationPosition.x + (Globals::locationSize - taxLocationSpriteWidth)/2, taxLocationPosition.y + (Globals::locationSize - taxLocationSpriteHeight)/2),
        sf::Vector2f(taxLocationSpriteWidth, taxLocationSpriteHeight)
    );

}

void InGameSceneCreator::createGamblingLocation()
{
    sf::Vector2f gamblingLocationPosition = sf::Vector2f(Globals::windowWidth - locationsPadding - Globals::locationSize + Globals::buttonBorderThickness*1.75, locationsPadding + 4*Globals::locationSize + 6.75*Globals::buttonBorderThickness);
    globals.getLocations()[12]->position = gamblingLocationPosition;
    UIRectangleShape* gamblingLocationSquare = new UIRectangleShape
    (
        globals.getInGameScene(),
        gamblingLocationPosition,
        sf::Vector2f(Globals::locationSize, Globals::locationSize),
        sf::Color::Black
    );    
    gamblingLocationSquare->setBorder(locationBorderSize, sf::Color::White);
    if(!gamblingLocationTexture.loadFromFile("Assets/Superbet.png"))
    {
        std::cerr << "Failed to load image" << std::endl;
    }
    UISprite* gamblingLocationSprite = new UISprite
    (
        globals.getInGameScene(),
        &gamblingLocationTexture,
        sf::Vector2f(gamblingLocationPosition.x + (Globals::locationSize - gamblingLocationSpriteSize)/2, gamblingLocationPosition.y + (Globals::locationSize - gamblingLocationSpriteSize)/2),
        sf::Vector2f(gamblingLocationSpriteSize, gamblingLocationSpriteSize)
    );

}

void InGameSceneCreator::createInGameSceneButtons()
{
    globals.setRollDiceButton(new Button(globals.getInGameScene(), rollDiceButtonPositionX, rollDiceButtonPositionY, Globals::buttonWidth, Globals::buttonHeight, globals.getGlobalFont(), "Roll Dice", globals.getButtonColor(), Globals::buttonBorderThickness, globals.getButtonBorderColor()));
    globals.getOutlineColorHoverButtons().push_back(globals.getRollDiceButton());
    globals.setBuyPropertyButton(new Button(globals.getInGameScene(), buyPropertyButtonPositionX, buyPropertyButtonPositionY, Globals::buttonWidth, Globals::buttonHeight, globals.getGlobalFont(), "Buy property", globals.getButtonColor(), Globals::buttonBorderThickness, globals.getButtonBorderColor()));
    globals.getOutlineColorHoverButtons().push_back(globals.getBuyPropertyButton());
    globals.setNextButton(new Button(globals.getInGameScene(), rollDiceButtonPositionX, rollDiceButtonPositionY, Globals::buttonWidth, Globals::buttonHeight, globals.getGlobalFont(), "Next", globals.getButtonColor(), Globals::buttonBorderThickness, globals.getButtonBorderColor()));
    globals.getOutlineColorHoverButtons().push_back(globals.getNextButton());
    globals.setBuyHouseButton(new Button(globals.getInGameScene(), buyHouseButtonPositionX, buyHouseButtonPositionY, Globals::buttonWidth, Globals::buttonHeight, globals.getGlobalFont(), "Buy home", globals.getButtonColor(), Globals::buttonBorderThickness, globals.getButtonBorderColor()));
    globals.getOutlineColorHoverButtons().push_back(globals.getBuyHouseButton());

    globals.setRollDiceResultText(new UIText(globals.getInGameScene(), globals.getGlobalFont(), rollDiceResultTextCharacterSize, "" ));
    globals.getRollDiceResultText()->setPosition(sf::Vector2f(rollDiceResultTextPositionX, rollDiceResultTextPositionY));
}

void InGameSceneCreator::createInGameClockText()
{
    globals.setInGameClockText(new UIText(globals.getInGameScene()));
    
}

void InGameSceneCreator::createGameOverScreen()
{
    globals.setGameOverText(new UIText(globals.getInGameScene(), globals.getGlobalFont(), gameOverTextCharacterSize, "Game Over"));
    globals.getGameOverText()->setPosition(sf::Vector2f(Globals::windowWidth/2-globals.getGameOverText()->getLocalBounds().width/2, gameOverTextPositionY));

    globals.setGameOverPlayingTimeText(new UIText(globals.getInGameScene(), globals.getGlobalFont(), gameOverPlayingTimeTextCharacterSize));
}

void InGameSceneCreator::createInGameScene()
{
    createLocationsHorizontalUp();
    createLocationsVerticalRight();
    createLocationsHorizontalDown();
    createLocationsVerticalLeft();
    createStart();
    createGoToJailLocation();
    createJailLocation();
    createTaxLocation();
    createGamblingLocation();
    createInGameSceneButtons();
    createInGameClockText();
    createGameOverScreen();

    globals.getInGameScene().hideAll();
}