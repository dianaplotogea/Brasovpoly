#include "Globals.h"


Globals globals;

bool Globals::getShouldStartGameButtonBeActivated()
{
    return shouldStartGameButtonBeActivated;
}

void Globals::setShouldStartGameButtonBeActivated(bool shouldStartGameButtonBeActivatedParam)
{
    shouldStartGameButtonBeActivated = shouldStartGameButtonBeActivatedParam;
}

bool Globals::getShouldInGameClockWork()
{
    return shouldInGameClockWork;
}

void Globals::setShouldInGameClockWork(bool shouldInGameClockWorkParam)
{
    shouldInGameClockWork = shouldInGameClockWorkParam;
}

UIContainer& Globals::getPlayerCountSelectionMenu()
{
    return playerCountSelectionMenu;
}

void Globals::setPlayerCountSelectionMenu(UIContainer playerCountSelectionMenuParam)
{
    playerCountSelectionMenu = playerCountSelectionMenuParam;
}

UIContainer& Globals::getTutorialMenu()
{
    return tutorialMenu;
}

UIContainer& Globals::getPlayerSetupMenu()
{
    return playerSetupMenu;
}

UIContainer& Globals::getPlayerColorSelectorMenu()
{
    return playerColorSelectorMenu;
}

UIContainer& Globals::getInGameScene()
{
    return inGameScene;
}

UIContainer& Globals::getEmptyUIContainer()
{
    return emptyUIContainer;
}

sf::Font* Globals::getGlobalFont()
{
    return &font;
}

sf::Color Globals::getButtonColor()
{
    return buttonColor;
}

sf::Color Globals::getButtonBorderColor()
{
    return buttonBorderColor;
}

std::vector<Location*>& Globals::getLocations()
{
    return locations;
}

std::vector<sf::Color>& Globals::getPlayerColors()
{
    return colors;
}

Globals::GameState& Globals::getCurrentState()
{
    return currentState;
}

void Globals::setCurrentState(Globals::GameState currentStateParam)
{
    currentState = currentStateParam;
}

Button* Globals::getRollDiceButton()
{
    return rollDiceButton;
}

void Globals::setRollDiceButton(Button* rollDiceButtonParam)
{
    rollDiceButton = rollDiceButtonParam;
}

Button* Globals::getBuyPropertyButton()
{
    return buyPropertyButton;
}

void Globals::setBuyPropertyButton(Button* buyPropertyButtonParam)
{
    buyPropertyButton = buyPropertyButtonParam;
}

Button* Globals::getNextButton()
{
    return nextButton;
}

void Globals::setNextButton(Button* nextButtonParam)
{
    nextButton = nextButtonParam;
}

Button* Globals::getBuyHouseButton()
{
    return buyHouseButton;
}

void Globals::setBuyHouseButton(Button* buyHouseButtonParam)
{
    buyHouseButton = buyHouseButtonParam;
}

std::vector<Button*>& Globals::getOutlineColorHoverButtons()
{
    return outlineColorHoverButtons;
}

void Globals::setOutlineColorHoverButtons(std::vector<Button*>& outlineColorHoverButtonsParam)
{
    outlineColorHoverButtons = outlineColorHoverButtonsParam;
}

std::vector<Button*>& Globals::getSpriteColorHoverButtons()
{
    return spriteColorHoverButtons;
}

void Globals::setSpriteColorHoverButtons(std::vector<Button*>& spriteColorHoverButtonsParam)
{
    spriteColorHoverButtons = spriteColorHoverButtonsParam;
}

UIText* Globals::getRollDiceResultText()
{
    return rollDiceResultText;
}

void Globals::setRollDiceResultText(UIText* rollDiceResultTextParam)
{
    rollDiceResultText = rollDiceResultTextParam;
}

UIText* Globals::getGameOverText()
{
    return gameOverText;
}

void Globals::setGameOverText(UIText* gameOverTextParam)
{
    gameOverText = gameOverTextParam;
}

UIText* Globals::getGameOverPlayingTimeText()
{
    return gameOverPlayingTimeText;
}

void Globals::setGameOverPlayingTimeText(UIText* gameOverPlayingTimeTextParam)
{
    gameOverPlayingTimeText = gameOverPlayingTimeTextParam;
}

UIText* Globals::getInGameClockText()
{
    return inGameClockText;
}

void Globals::setInGameClockText(UIText* inGameClockTextParam)
{
    inGameClockText = inGameClockTextParam;
}

sf::Clock* Globals::getPlayingTimeClock()
{
    return playingTimeClock;
}

void Globals::setPlayingTimeClock(sf::Clock* playingTimeClockParam)
{
    playingTimeClock = playingTimeClockParam;
}

std::vector<UIText*>& Globals::getLeaderBoardNameTexts()
{
    return leaderBoardNameTexts;
}

void Globals::setLeaderBoardNameTexts(std::vector<UIText*>& leaderBoardNameTextsParam)
{
    leaderBoardNameTexts = leaderBoardNameTextsParam;
}

UISprite* Globals::getCloseButtonUISpritePlayerCountSelectionMenu()
{
    return closeButtonUISpritePlayerCountSelectionMenu;
}

void Globals::setCloseButtonUISpritePlayerCountSelectionMenu(UISprite* closeButtonUISpritePlayerCountSelectionMenuParam)
{
    closeButtonUISpritePlayerCountSelectionMenu = closeButtonUISpritePlayerCountSelectionMenuParam;
}

UISprite* Globals::getTutorialButtonUISprite()
{
    return tutorialButtonUISprite;
}

void Globals::setTutorialButtonUISprite(UISprite* tutorialButtonUISpriteParam)
{
    tutorialButtonUISprite = tutorialButtonUISpriteParam;
}

std::vector<Player*>& Globals::getPlayers()
{
    return players;
}

void Globals::setPlayers(std::vector<Player*>& playersParam)
{
    players = playersParam;
}

std::vector<Player*>& Globals::getPlayersInWinningOrder()
{
    return playersInWinningOrder;
}

void Globals::setPlayersInWinningOrder(std::vector<Player*>& playersInWinningOrderParam)
{
    playersInWinningOrder = playersInWinningOrderParam;
}

std::vector<UIElement*>& Globals::getInGameSceneUIElementsThatMustBeDeleted()
{
    return inGameSceneUIElementsThatMustBeDeleted;
}

void Globals::setInGameSceneUIElementsThatMustBeDeleted(std::vector<UIElement*>& inGameSceneUIElementsThatMustBeDeletedParam)
{
    inGameSceneUIElementsThatMustBeDeleted = inGameSceneUIElementsThatMustBeDeletedParam;
}

std::vector<UIRectangleShape*>& Globals::getPropertyColorSquares()
{
    return propertyColorSquares;
}

void Globals::setPropertyColorSquares(std::vector<UIRectangleShape*>& propertyColorSquaresParam)
{
    propertyColorSquares = propertyColorSquaresParam;
}

Button* Globals::getTutorialButton()
{
    return tutorialButton;
}

Button* Globals::getCloseButton()
{
    return closeButton;
}

Button* Globals::getStartGameButton()
{
    return startGameButton;
}

void Globals::setCloseButton(Button* closeButtonParam)
{
    closeButton = closeButtonParam;
}

void Globals::setTutorialButton(Button* tutorialButtonParam)
{
    tutorialButton = tutorialButtonParam;
}

void Globals::setStartGameButton(Button* startGameButtonParam)
{
    startGameButton = startGameButtonParam;
}