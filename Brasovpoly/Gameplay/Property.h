#ifndef PROPERTY_H
#define PROPERTY_H

#include "Location.h"

class Player; // Player includes Property as well so forward declaration is needed

class Property : public Location
{
public:
    int price;

    std::string name;

    UIRectangleShape* propertyColorSquare;

    Player* owner; // It has to be marked with *, because it's not present in the constructor

    Property(std::string nameParam, int priceParam)
    : name(nameParam), price(priceParam), owner(nullptr) {}; // An object is not nullptr by default, so it has to be set to nullptr here

};

#endif