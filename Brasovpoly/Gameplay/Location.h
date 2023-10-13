#ifndef LOCATION_H
#define LOCATION_H

#include <SFML/Graphics.hpp>

class Location
{
public:
    virtual ~Location() {} // It is needed, because we have to cast it to become a property, when we are creating the inGameScene
    sf::Vector2f position;
};

#endif