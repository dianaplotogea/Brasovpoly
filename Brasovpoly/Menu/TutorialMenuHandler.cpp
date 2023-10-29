#include <iostream>
#include "TutorialMenuHandler.h"
#include "../Globals.h"
#include "../UI/Button.h"
#include "../UI/UIText.h"



void TutorialMenuHandler::tutorialButtonEventHandler(sf::RenderWindow& window)
{
    if(globals.getTutorialButton()->isMouseOver(window))
    {
        std::cout << "if(tutorialButton->isMouseOver(window))" << std::endl;
        globals.getPlayerCountSelectionMenu().hideAll();
        globals.getTutorialMenu().showAll();
        globals.setCurrentState(Globals::GameState::TutorialMenu);
    }
}

void TutorialMenuHandler::createTutorialMenu()
{
    std::cout << "createTutorialMenu()" << std::endl;
    for(int i=0;i<rules.size();i++)
    {
        std::cout << rules[i] << std::endl;
        UIText* ruleText = new UIText(globals.getTutorialMenu(), globals.getGlobalFont(), ruleTextCharacterSize, rules[i]);
        ruleText->setPosition(sf::Vector2f(Globals::windowWidth/2- ruleText->getLocalBounds().width/2, ruleTextInitialPositionY + i*distanceBetweenRuleTextsY));
    }
    UIText* tutorialText = new UIText(globals.getTutorialMenu(), globals.getGlobalFont(), tutorialTextCharacterSize, "Tutorial");
    tutorialText->setPosition(sf::Vector2f(Globals::windowWidth/2-tutorialText->getLocalBounds().width/2, tutorialTitlePositionY));
    globals.getTutorialMenu().hideAll();
}