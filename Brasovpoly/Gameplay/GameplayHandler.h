#ifndef GAMEPLAY_HANDLER_H
#define GAMEPLAY_HANDLER_H

#include <SFML/Graphics.hpp>

extern int percentOfPropertyPriceWhichHasToBePaidWhenPropertyIsVisited;

void startGameButtonEventHandler(sf::RenderWindow& window);
void rollDiceButtonEventHandler(sf::RenderWindow& window);
void buyPropertyButtonEventHandler(sf::RenderWindow& window);
void nextButtonEventHandler(sf::RenderWindow& window);
void buyHouseButtonEventHandler(sf::RenderWindow& window);
void activateBuyHouseButtonIfPlayerCanBuyIt();

#endif