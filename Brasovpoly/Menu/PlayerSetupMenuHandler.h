#ifndef PLAYER_SETUP_MENU_HANDLER_H
#define PLAYER_SETUP_MENU_HANDLER_H

#include "../Player.h"

class PlayerSetupMenuHandler
{
public:
    void createPlayerSetupMenu(int numberOfPlayers);
    void selectPlayerSetupMenuInput(sf::RenderWindow& window, sf::Event event);
    void handleEnteredTextSelectPlayerSetupMenu(sf::Event event);
    void activateStartGameButtonIfAllPlayersAreSet();
    void createStartGameButton();
private:
    int initialPositionX = 0;
    int distanceBetweenElementsX = 250;
    int textPositionY = 150;
    int inputFieldPositionY = 250;
    int colorButtonPositionY = 350;
    int colorButtonWidth = 150;
    int colorButtonHeight = 50;
    int inputTextPosition = 50;

    int inputFieldWidth = 220;
    int inputFieldHeight = 24;

    int startGameButtonWidth = 200;
    int startGameButtonHeight = 50;
    int startGameButtonDistanceFromBottom = 100;

    std::string inputString;

    sf::Text inputText;
};


#endif