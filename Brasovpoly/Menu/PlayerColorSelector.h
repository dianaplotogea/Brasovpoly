#ifndef PLAYER_COLOR_SELECTOR_H
#define PLAYER_COLOR_SELECTOR_H

#include <SFML/Graphics.hpp>
#include "../UI/Button.h"
#include "../UI/UIText.h"
#include "../Player.h"



class PlayerColorSelector
{
public:
    void createColorSelectorMenu();
    void colorButtonEventHandler(sf::RenderWindow& window);
    void colorSelectorButtonEventHandler(sf::RenderWindow& window);
private:
    int numberOfColumns = 3;
    int distanceBetweenElements = 100;
    int colorSelectorButtonWidth = 100;
    int colorSelectorButtonHeight = 100;
    int colorSelectorButtonPositionX = (Globals::windowWidth - numberOfColumns * colorSelectorButtonWidth - (numberOfColumns-1) * distanceBetweenElements)/2;
    int colorSelectorButtonInitialPositionY = 225;
    int colorSelectorButtonPositionY = 100;

    int playerColorSelectorTextPositionY = 200;
    int playerColorSelectorTextCharacterSize = 30;

    std::vector<Button*> colorSelectorButtons;

    UIText* playerColorSelectorText;

    Player* currentPlayer;

    Button* previousColorSelectorButton = nullptr;
};

#endif