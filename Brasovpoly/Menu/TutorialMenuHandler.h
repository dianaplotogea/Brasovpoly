#ifndef TUTORIAL_MENU_HANDLER_H
#define TUTORIAL_MENU_HANDLER_H

#include <SFML/Graphics.hpp>
#include "../Gameplay/GameplayHandler.h"

class TutorialMenuHandler
{
    int ruleTextCharacterSize = 25;
    int ruleTextInitialPositionY = 200;
    int distanceBetweenRuleTextsY = 40;

    int tutorialTitlePositionY = 100;
    int tutorialTextCharacterSize = 45;

    GameplayHandler gameplayHandler;

    std::vector<std::string> rules
    {
    "-Select the number of players",
    "-After selecting the number of players, choose a name and a color for each. A default color is already set for convenience",
    "-Each player must have a unique name and a unique color",
    "-A player's name cannot be empty",
    "-Once all players are set, press the 'Start Game' button",
    "-Each player can roll the dice when it's their turn",
    "-If a player lands on an unowned property, they can choose to buy it or not",
    "-If a player lands on a property that is already owned, they must pay " + std::to_string(gameplayHandler.getPercentOfPropertyPriceWhichHasToBePaidWhenPropertyIsVisited()) + "% of the property's initial value",
    "-A player who runs out of money is eliminated from the game",
    "-The game continues until only one player remains"
    
    };
public:
    void tutorialButtonEventHandler(sf::RenderWindow& window);
    void createTutorialMenu();
};



#endif