#ifndef PROPERTY_H
#define PROPERTY_H

#include "District.h"
#include "Location.h"

class Player; // Player includes Property as well so forward declaration is needed

class Property : public Location
{
public:
    int price;

    std::string name;

    UIRectangleShape* propertyColorSquare;

    District district;

    Player* owner; // It has to be marked with *, because it's not present in the constructor

    Property(std::string nameParam, District districtParam, int priceParam)
    : name(nameParam), district(districtParam), price(priceParam), owner(nullptr) {}; // An object is not nullptr by default, so it has to be set to nullptr here

};

#endif