#ifndef PROPERTY_H
#define PROPERTY_H

#include "Location.h"
#include "../UI/UIRectangleShape.h"

class Player; // Player includes Property as well so forward declaration is needed

class Property : public Location
{
public:
    Property(std::string nameParam, int priceParam)
    : name(nameParam), price(priceParam), owner(nullptr) {}; // An object is not nullptr by default, so it has to be set to nullptr here

    int getPrice();

    std::string getName();

    Player* getOwner();
    void setOwner(Player* ownerParam);

    UIRectangleShape* getPropertyColorSquare();
    void setPropertyColorSquare(UIRectangleShape* propertyColorSquareParam);

private:
    int price;

    std::string name;

    UIRectangleShape* propertyColorSquare;

    Player* owner;
};

#endif