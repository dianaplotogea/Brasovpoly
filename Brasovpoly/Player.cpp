#include "Player.h"

void Player::setMoneyAmount(int moneyAmountParam)
{
    moneyAmount = moneyAmountParam;
}

int Player::getMoneyAmount()
{
    return moneyAmount;
}

int Player::getCount()
{
    return count;
}

int Player::getTransportPropertyAmount()
{
    return transportPropertyAmount;
}

void Player::incrementTransportPropertyAmount()
{
    transportPropertyAmount++;
}

int Player::getNumberOfTurnsSinceJail()
{
    return numberOfTurnsSinceJail;
}

void Player::setNumberOfTurnsSinceJail(int numberOfTurnsSinceJailParam)
{
    numberOfTurnsSinceJail = numberOfTurnsSinceJailParam;
}

void Player::incrementNumberOfTurnsSinceJail()
{
    numberOfTurnsSinceJail++;
}

bool Player::getIsInJail()
{
    return isInJail;
}

void Player::setIsInJail(bool isInJailParam)
{
    isInJail = isInJailParam;
}

std::string Player::getName()
{
    return name;
}

void Player::setName(std::string nameParam)
{
    name = nameParam;
}

sf::Color Player::getColor()
{
    return color;
}

void Player::setColor(sf::Color colorParam)
{
    color = colorParam;
}

UIText* Player::getPlayerIndexText()
{
    return playerIndexText;
}

UIText* Player::getPlayerNameText()
{
    return playerNameText;
}

void Player::setPlayerNameText(UIText* playerNameTextParam)
{
    playerNameText = playerNameTextParam;
}

UIText* Player::getPlayerMoneyAmountText()
{
    return playerMoneyAmountText;
}

void Player::setPlayerMoneyAmountText(UIText* playerMoneyAmountTextParam)
{
    playerMoneyAmountText = playerMoneyAmountTextParam;
}

UIText* Player::getPlayerProfitAmountText()
{
    return playerProfitAmountText;
}

void Player::setPlayerProfitAmountText(UIText* playerProfitAmountTextParam)
{
    playerProfitAmountText = playerProfitAmountTextParam;
}

UIRectangleShape* Player::getUiRectangleShapePlayer()
{
    return uiRectangleShapePlayer;
}

void Player::setUiRectangleShapePlayer(UIRectangleShape* uiRectangleShapePlayerParam)
{
    uiRectangleShapePlayer = uiRectangleShapePlayerParam;        
}

Location* Player::getCurrentLocation()
{
    return currentLocation;
}

void Player::setCurrentLocation(Location* currentLocationParam)
{
    currentLocation = currentLocationParam;
}

std::vector<Property*> Player::getOwnedProperties()
{
    return ownedProperties;
}

void Player::addProperty(Property* property)
{
    ownedProperties.push_back(property);
}

InputField* Player::getInputField()
{
    return inputField;
}

Button* Player::getColorButton()
{
    return colorButton;
}