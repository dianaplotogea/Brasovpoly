#ifndef PLAYER_COUNT_SELECTION_MENU_HANDLER_H
#define PLAYER_COUNT_SELECTION_MENU_HANDLER_H

#include <SFML/Graphics.hpp>
#include "../UI/Button.h"



class PlayerCountSelectionMenuHandler
{
public:
    void createPlayerCountSelectionMenu();
    void playerCountSelectionButtonsEventHandler(sf::RenderWindow& window);
private:
    int maximumNumberOfPlayers = 6;
    int playerCountSelectionButtonInitialPositionY = 150;
    int playerCountSelectionButtonDistanceBetweenButtonsY = 100;
    int playerCountSelectionTextPositionY = 200;
    int playerCountSelectionTextCharacterSize = 30;

    int tutorialButtonPadding = 30;
    int tutorialButtonSize = 45;

    std::vector<Button*> playerCountSelectionButtons;

    sf::Texture tutorialButtonTexture;
};

#endif