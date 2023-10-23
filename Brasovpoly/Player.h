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

    Location * currentLocation;

    std::vector<Property*> ownedProperties;

    InputField* inputField;
    
    Button* colorButton;

    Player(int countParam, UIText* playerIndexTextParam, InputField* inputFieldParam, Button* colorButtonParam, sf::Color colorParam) 
    : count(countParam), playerIndexText(playerIndexTextParam), inputField(inputFieldParam), colorButton(colorButtonParam), color(colorParam) {};

};

#endif