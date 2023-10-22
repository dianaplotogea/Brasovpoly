#ifndef DISTRICT_H
#define DISTRICT_H

#include <SFML/Graphics.hpp>
#include <string>

class District
{
public:
    std::string name;
    sf::Color color;
    District(std::string nameParam, sf::Color colorParam)
    : name(nameParam), color(colorParam) {};
};

#endif