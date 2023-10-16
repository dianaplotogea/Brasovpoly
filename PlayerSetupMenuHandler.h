#ifndef PLAYER_SETUP_MENU_HANDLER_H
#define PLAYER_SETUP_MENU_HANDLER_H

#include "Player.h"

void createPlayerSetupMenu(int numberOfPlayers);
void closePlayerSetupMenu(sf::RenderWindow& window);
void selectPlayerSetupMenuInput(sf::RenderWindow& window, sf::Event event);
void handleEnteredTextSelectPlayerSetupMenu(sf::Event event);
void activateStartGameButtonIfAllPlayersAreSet();
void createStartGameButton();

#endif