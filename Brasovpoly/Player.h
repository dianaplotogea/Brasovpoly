#ifndef PLAYER_H
#define PLAYER_H

class Button;
class UIText;

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