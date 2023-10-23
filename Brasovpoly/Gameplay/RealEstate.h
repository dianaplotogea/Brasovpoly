#ifndef REAL_ESTATE_H
#define REAL_ESTATE_H

#include "Property.h"

class RealEstate : public Property
{
public:
    int houseAmount = 0;
    std::vector<UISprite*> houseSprites;
    RealEstate(std::string nameParam, int priceParam)
        : Property(nameParam, priceParam) {}
};

#endif