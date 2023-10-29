#ifndef REAL_ESTATE_H
#define REAL_ESTATE_H

#include "Property.h"
#include "../UI/UISprite.h"

class RealEstate : public Property
{
public:
    RealEstate(std::string nameParam, int priceParam)
        : Property(nameParam, priceParam) {}

    int getHouseAmount();
    void incrementHouseAmount();

    void clearHouseSprites();

    std::vector<UISprite*> getHouseSprites();
    void addHouseSprite(UISprite* uiSprite);
    
private:
    int houseAmount = 0;
    std::vector<UISprite*> houseSprites;
};

#endif