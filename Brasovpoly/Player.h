#ifndef PLAYER_H
#define PLAYER_H

class Button; // Button includes Globals.h and GLobals.h includes Player
class UIText; // UIText includes Globals.h and Globals.h includes Player

#include <string>
#include <SFML/Graphics.hpp>
#include "UI/InputField.h"
#include "UI/UIRectangleShape.h"
#include "Gameplay/Property.h"

class Player
{
public:
    Player(int countParam, UIText* playerIndexTextParam, InputField* inputFieldParam, Button* colorButtonParam, sf::Color colorParam) 
    : count(countParam), playerIndexText(playerIndexTextParam), inputField(inputFieldParam), colorButton(colorButtonParam), color(colorParam) {};

    void setMoneyAmount(int moneyAmountParam);

    int getMoneyAmount();

    int getCount();

    int getTransportPropertyAmount();

    void incrementTransportPropertyAmount();

    int getNumberOfTurnsSinceJail();

    void setNumberOfTurnsSinceJail(int numberOfTurnsSinceJailParam);

    void incrementNumberOfTurnsSinceJail();

    bool getIsInJail();

    void setIsInJail(bool isInJailParam);

    std::string getName();

    void setName(std::string nameParam);
    sf::Color getColor();

    void setColor(sf::Color colorParam);

    UIText* getPlayerIndexText();

    UIText* getPlayerNameText();

    void setPlayerNameText(UIText* playerNameTextParam);

    UIText* getPlayerMoneyAmountText();

    void setPlayerMoneyAmountText(UIText* playerMoneyAmountTextParam);

    UIText* getPlayerProfitAmountText();

    void setPlayerProfitAmountText(UIText* playerProfitAmountTextParam);

    UIRectangleShape* getUiRectangleShapePlayer();

    void setUiRectangleShapePlayer(UIRectangleShape* uiRectangleShapePlayerParam);

    Location* getCurrentLocation();

    void setCurrentLocation(Location* currentLocationParam);

    std::vector<Property*> getOwnedProperties();

    void addProperty(Property* property);

    InputField* getInputField();

    Button* getColorButton();

private:
    int count;
    int moneyAmount;
    int transportPropertyAmount = 0;
    int numberOfTurnsSinceJail = 0;

    bool isInJail = false;

    std::string name;

    sf::Color color;

    UIText* playerIndexText;
    UIText* playerNameText;
    UIText* playerMoneyAmountText;
    UIText* playerProfitAmountText;

    UIRectangleShape* uiRectangleShapePlayer;

    Location* currentLocation;

    std::vector<Property*> ownedProperties;

    InputField* inputField;

    Button* colorButton;

};

#endif