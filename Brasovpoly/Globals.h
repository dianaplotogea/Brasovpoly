#ifndef GLOBALS_H
#define GLOBALS_H


#include "Player.h"
#include "Gameplay/Start.h"
#include "Gameplay/Property.h"
#include "Gameplay/TransportProperty.h"
#include "Gameplay/RealEstate.h"
#include "Gameplay/GoToJailLocation.h"
#include "Gameplay/JailLocation.h"
#include "Gameplay/TaxLocation.h"
#include "Gameplay/GamblingLocation.h"
#include "UI/UIText.h"
#include "UI/UIContainer.h"
#include "UI/Button.h"

class Button;
class UIText;

class Globals
{
public:
    static const int windowWidth = 1530;
    static const int windowHeight = 960;
    static const int buttonWidth = 200;
    static const int buttonHeight = 75;
    static const int buttonBorderThickness = 3;
    static const int locationSize = 150;

    enum class GameState
    {
        PlayerCountSelection,
        TutorialMenu,
        PlayerSetup,
        PlayerColorSelection,
        InGame
    };

    bool getShouldStartGameButtonBeActivated();

    void setShouldStartGameButtonBeActivated(bool shouldStartGameButtonBeActivatedParam);

    bool getShouldInGameClockWork();

    void setShouldInGameClockWork(bool shouldInGameClockWorkParam);

    UIContainer& getPlayerCountSelectionMenu();

    void setPlayerCountSelectionMenu(UIContainer playerCountSelectionMenuParam);

    UIContainer& getTutorialMenu();

    UIContainer& getPlayerSetupMenu();

    UIContainer& getPlayerColorSelectorMenu();

    UIContainer& getInGameScene();

    UIContainer& getEmptyUIContainer();

    sf::Font* getGlobalFont();

    sf::Color getButtonColor();

    sf::Color getButtonBorderColor();

    std::vector<Location*>& getLocations();

    std::vector<sf::Color>& getPlayerColors();

    GameState& getCurrentState();

    void setCurrentState(Globals::GameState currentStateParam);

    Button* getTutorialButton();
    void setTutorialButton(Button* tutorialButtonParam);

    Button* getCloseButton();
    void setCloseButton(Button* closeButtonParam);

    Button* getStartGameButton();
    void setStartGameButton(Button* startGameButtonParam);

    Button* getRollDiceButton();
    void setRollDiceButton(Button* rollDiceButtonParam);

    Button* getBuyPropertyButton();
    void setBuyPropertyButton(Button* buyPropertyButtonParam);

    Button* getNextButton();
    void setNextButton(Button* nextButtonParam);

    Button* getBuyHouseButton();
    void setBuyHouseButton(Button* buyHouseButtonParam);

    std::vector<Button*>& getOutlineColorHoverButtons();
    void setOutlineColorHoverButtons(std::vector<Button*>& outlineColorHoverButtonsParam);

    std::vector<Button*>& getSpriteColorHoverButtons();
    void setSpriteColorHoverButtons(std::vector<Button*>& spriteColorHoverButtonsParam);

    UIText* getRollDiceResultText();
    void setRollDiceResultText(UIText* rollDiceResultTextParam);

    UIText* getGameOverText();
    void setGameOverText(UIText* gameOverTextParam);

    UIText* getGameOverPlayingTimeText();
    void setGameOverPlayingTimeText(UIText* gameOverPlayingTimeTextParam);

    UIText* getInGameClockText();
    void setInGameClockText(UIText* inGameClockTextParam);

    sf::Clock* getPlayingTimeClock();
    void setPlayingTimeClock(sf::Clock* playingTimeClockParam);

    std::vector<UIText*>& getLeaderBoardNameTexts();
    void setLeaderBoardNameTexts(std::vector<UIText*>& leaderBoardNameTextsParam);

    UISprite* getCloseButtonUISpritePlayerCountSelectionMenu();
    void setCloseButtonUISpritePlayerCountSelectionMenu(UISprite* closeButtonUISpritePlayerCountSelectionMenuParam);

    UISprite* getTutorialButtonUISprite();
    
    void setTutorialButtonUISprite(UISprite* tutorialButtonUISpriteParam);

    std::vector<Player*>& getPlayers();
    void setPlayers(std::vector<Player*>& playersParam);

    std::vector<Player*>& getPlayersInWinningOrder();
    void setPlayersInWinningOrder(std::vector<Player*>& playersInWinningOrderParam);

    std::vector<UIElement*>& getInGameSceneUIElementsThatMustBeDeleted();
    void setInGameSceneUIElementsThatMustBeDeleted(std::vector<UIElement*>& inGameSceneUIElementsThatMustBeDeletedParam);

    std::vector<UIRectangleShape*>& getPropertyColorSquares();
    void setPropertyColorSquares(std::vector<UIRectangleShape*>& propertyColorSquaresParam);


private:
    bool shouldStartGameButtonBeActivated = false;
    bool shouldInGameClockWork = false;

    UIContainer playerCountSelectionMenu;
    UIContainer tutorialMenu;
    UIContainer playerSetupMenu;
    UIContainer playerColorSelectorMenu;
    UIContainer inGameScene;
    UIContainer emptyUIContainer;

    sf::Font font;

    sf::Color buttonColor = sf::Color::Black;
    sf::Color buttonBorderColor = sf::Color::White;

    std::vector<Location*> locations
    {
        new Start(),

        new RealEstate("Piata Sfatului", 5000),
        new RealEstate("Livada Postei", 4500),
        new RealEstate("Primaria", 3900),

        new TransportProperty("Gara", 100, "Train.png"),
        new RealEstate("Biserica Bartolomeu", 400),
        new RealEstate("Hornbach", 50),

        new RealEstate("Piata Astra", 900),
    
        new GoToJailLocation(),
        new RealEstate("Coresi", 2200),
        new TransportProperty("RATBV", 100, "Bus.png"),
        new RealEstate("Kaufland", 400),
        new GamblingLocation(),

        new RealEstate("eMAG", 3100),
        new TaxLocation(),
        new RealEstate("Dealul Melcilor", 1200),
        new TransportProperty("Aeroport", 100, "Plane.png"),
        new RealEstate("Decathlon", 900),

        new RealEstate("Belvedere", 4500),

        new RealEstate("Gradina Zoologica", 1200),
        new JailLocation(),
        new RealEstate("Carrefour", 1000),
        new TransportProperty("Martax", 100, "Taxi.png"),
        new RealEstate("Jumbo", 600),

    };

    std::vector<sf::Color> colors =
    {
        {153, 101, 21}, // Brown
        {1, 50, 32}, // Dark green
        {255, 192, 203}, // Pink
        {128, 0, 128}, // Purple
        {255, 165, 0}, // Orange
        {190, 207, 64}, // Yellow
        {207, 64, 64}, // Red
        {64, 88, 207}, // Blue
        {144, 238, 144} // Light green
    };

    GameState currentState = GameState::PlayerCountSelection;

    Button* tutorialButton;
    Button* closeButton;
    Button* startGameButton;
    Button* rollDiceButton;
    Button* buyPropertyButton;
    Button* nextButton;
    Button* buyHouseButton;

    std::vector<Button*> outlineColorHoverButtons;
    std::vector<Button*> spriteColorHoverButtons;

    UIText* rollDiceResultText;
    UIText* gameOverText;
    UIText* gameOverPlayingTimeText;
    UIText* inGameClockText;

    sf::Clock* playingTimeClock = new sf::Clock();

    std::vector<UIText*> leaderBoardNameTexts;

    UISprite* closeButtonUISpritePlayerCountSelectionMenu;
    UISprite* tutorialButtonUISprite;

    std::vector<Player*> players;
    std::vector<Player*> playersInWinningOrder;

    std::vector<UIElement*> inGameSceneUIElementsThatMustBeDeleted;

    std::vector<UIRectangleShape*> propertyColorSquares;
    
};

extern Globals globals;


#endif