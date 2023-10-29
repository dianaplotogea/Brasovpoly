#include "RealEstate.h"

int RealEstate::getHouseAmount()
{
    return houseAmount;
}

void RealEstate::incrementHouseAmount()
{
    houseAmount++;
}

void RealEstate::clearHouseSprites()
{
    houseSprites.clear();
}

std::vector<UISprite*> RealEstate::getHouseSprites()
{
    return houseSprites;
}

void RealEstate::addHouseSprite(UISprite* uiSprite)
{
    houseSprites.push_back(uiSprite);
}