#include "Property.h"

int Property::getPrice()
{
    return price;
}

std::string Property::getName()
{
    return name;
}

Player* Property::getOwner()
{
    return owner;
}

void Property::setOwner(Player* ownerParam)
{
    owner = ownerParam;
}

UIRectangleShape* Property::getPropertyColorSquare()
{
    return propertyColorSquare;
}

void Property::setPropertyColorSquare(UIRectangleShape* propertyColorSquareParam)
{
    propertyColorSquare = propertyColorSquareParam;
}