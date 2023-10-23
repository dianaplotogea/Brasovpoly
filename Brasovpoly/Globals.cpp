#include "Globals.h"
#include "Gameplay/Start.h"
#include "Gameplay/Property.h"
#include "Gameplay/TransportProperty.h"
#include "Gameplay/RealEstate.h"
#include "Gameplay/GoToJailLocation.h"
#include "Gameplay/JailLocation.h"
#include "Gameplay/TaxLocation.h"
#include "Gameplay/GamblingLocation.h"

int windowWidth = 1530;
int windowHeight = 960;
int buttonWidth = 200;
int buttonHeight = 75;
int buttonBorderThickness = 3;
int backButtonPosition = 100;
int locationSize = 150;

bool shouldStartGameButtonBeActivated = false;
bool shouldInGameClockWork = false;

UIContainer playerCountSelectionMenu;
UIContainer tutorialMenu;
UIContainer playerSetupMenu;
UIContainer playerColorSelectorMenu;
UIContainer inGameScene;

sf::Font font;

sf::Font* getGlobalFont()
{
    return &font;
}

sf::Color buttonColor = sf::Color::Black;
sf::Color buttonBorderColor = sf::Color::White;

UIContainer emptyUIContainer;

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

std::vector<UIElement*> inGameSceneUIElementsThatMustBeDeleted;

std::vector<UIRectangleShape*> propertyColorSquares;

GameState currentState = GameState::PlayerCountSelection;