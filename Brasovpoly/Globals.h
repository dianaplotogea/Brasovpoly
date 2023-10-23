#ifndef GLOBALS_H
#define GLOBALS_H

#include <SFML/Graphics.hpp>

sf::Font* getGlobalFont(); // A getter is needed in order to put it as a default value in the constructor of the Button. It has to be declared here, don't move it down

#include <vector>
#include "UI/UIContainer.h"
#include "Player.h"
#include "UI/UISprite.h"
#include "UI/UIRectangleShape.h"
#include "Gameplay/Location.h"

extern int windowWidth;
extern int windowHeight;
extern int buttonWidth;
extern int buttonHeight;
extern int buttonBorderThickness;
extern int backButtonPosition;
extern int locationSize;

extern bool shouldStartGameButtonBeActivated;
extern bool shouldInGameClockWork;

extern UIContainer playerCountSelectionMenu;
extern UIContainer tutorialMenu;
extern UIContainer playerSetupMenu;
extern UIContainer playerColorSelectorMenu;
extern UIContainer inGameScene;

extern sf::Font font;

extern sf::Color buttonColor;
extern sf::Color buttonBorderColor;

extern Button* tutorialButton;
extern Button* closeButton;
extern Button* startGameButton;
extern Button* rollDiceButton;
extern Button* buyPropertyButton;
extern Button* nextButton;
extern Button* buyHouseButton;;

extern std::vector<Button*> outlineColorHoverButtons;
extern std::vector<Button*> spriteColorHoverButtons;

extern UIText* rollDiceResultText;
extern UIText* gameOverText;
extern UIText* gameOverPlayingTimeText;
extern UIText* inGameClockText;

extern sf::Clock* playingTimeClock;

extern std::vector<UIText*> leaderBoardNameTexts;

extern UISprite* closeButtonUISpritePlayerCountSelectionMenu;
extern UISprite* tutorialButtonUISprite;
 
extern std::vector<Player*> players;
extern std::vector<Player*> playersInWinningOrder;

extern std::vector<Location*> locations;

extern std::vector<sf::Color> colors;

extern std::vector<UIElement*> inGameSceneUIElementsThatMustBeDeleted;

extern UIContainer emptyUIContainer; // It is needed for UI elements that are present in more than one state of the game

extern std::vector<UIRectangleShape*> propertyColorSquares;

enum class GameState
{
    PlayerCountSelection,
    TutorialMenu,
    PlayerSetup,
    PlayerColorSelection,
    InGame
};

extern GameState currentState;

#endif