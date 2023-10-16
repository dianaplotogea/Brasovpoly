#include <iostream>
#include "TutorialMenuHandler.h"
#include "../Globals.h"
#include "../UI/Button.h"
#include "../Gameplay/GameplayHandler.h"
#include "../UI/UIText.h"

int ruleTextCharacterSize = 25;
int ruleTextInitialPositionY = 200;
int distanceBetweenRuleTextsY = 40;

int tutorialTitlePositionY = 100;
int tutorialTextCharacterSize = 45;

std::vector<std::string> rules
{
    "-Select the number of players",
    "-After selecting the number of players, choose a name and a color for each. A default color is already set for convenience",
    "-Each player must have a unique name and a unique color",
    "-A player's name cannot be empty",
    "-Once all players are set, press the 'Start Game' button",
    "-Each player can roll the dice when it's their turn",
    "-If a player lands on an unowned property, they can choose to buy it or not",
    "-If a player lands on a property that is already owned, they must pay " + std::to_string(percentOfPropertyPriceWhichHasToBePaidWhenPropertyIsVisited) + "% of the property's initial value",
    "-A player who runs out of money is eliminated from the game",
    "-The game continues until only one player remains"
    
};

void tutorialButtonEventHandler(sf::RenderWindow& window)
{
    if(tutorialButton->isMouseOver(window))
    {
        std::cout << "if(tutorialButton->isMouseOver(window))" << std::endl;
        playerCountSelectionMenu.hideAll();
        tutorialMenu.showAll();
        currentState = GameState::TutorialMenu;
    }
}

void createTutorialMenu()
{
    for(int i=0;i<rules.size();i++)
    {
        std::cout << rules[i] << std::endl;
        UIText* ruleText = new UIText(tutorialMenu, &font, ruleTextCharacterSize, rules[i]);
        ruleText->setPosition(sf::Vector2f(windowWidth/2- ruleText->getLocalBounds().width/2, ruleTextInitialPositionY + i*distanceBetweenRuleTextsY));
    }
    UIText* tutorialText = new UIText(tutorialMenu, &font, tutorialTextCharacterSize, "Tutorial");
    tutorialText->setPosition(sf::Vector2f(windowWidth/2-tutorialText->getLocalBounds().width/2, tutorialTitlePositionY));
    tutorialMenu.hideAll();
}