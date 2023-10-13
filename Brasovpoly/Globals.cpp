#include "Globals.h"
#include "Gameplay/Start.h"
#include "Gameplay/Property.h"

int windowWidth = 1530;
int windowHeight = 960;
int buttonWidth = 200;
int buttonHeight = 75;
int buttonBorderThickness = 3;
int backButtonPosition = 100;

bool shouldStartGameButtonBeActivated = false;

UIContainer playerCountSelectionMenu;
UIContainer playerSetupMenu;
UIContainer playerColorSelectorMenu;
UIContainer inGameScene;

sf::Font font;

sf::Color buttonColor = sf::Color::Black;
sf::Color buttonBorderColor = sf::Color::White;

sf::Font* getGlobalFont()
{
    return &font;
}

UIContainer emptyUIContainer;

Button* closeButton;
Button* startGameButton;
Button* rollDiceButton;
Button* buyPropertyButton;
Button* nextButton;

UIText* rollDiceResultText;

UISprite* closeButtonUISpritePlayerCountSelectionMenu;

std::vector<Player*> players;

std::vector<District> districts
{
    District("Centru", sf::Color::White),
    District("Bartolomeu", sf::Color::White),
    District("Astra", sf::Color::White),
    District("Tractorul", sf::Color::White),
    District("Centrul nou", sf::Color::White),
    District("Ragadau", sf::Color::White),
    District("Poiana", sf::Color::White),
    District("Noua", sf::Color::White),
    District("Darste", sf::Color::White)
};

std::vector<Location*> locations
{
    new Start(),

    new Property("Piata Sfatului", districts[0], 5000),
    new Property("Livada Postei", districts[0], 4500),
    new Property("Primaria", districts[0], 3900),

    new Property("Gara Bartolomenu", districts[1], 100),
    new Property("Biserica Bartolomeu", districts[1], 400),
    new Property("Hornbach", districts[1], 50),

    new Property("Piata Astra", districts[2], 900),
    new Property("Berzei", districts[2], 1000),
    new Property("Lidl", districts[2], 1200),

    new Property("Coresi", districts[3], 2200),
    new Property("Gara", districts[3], 400),
    new Property("Kronwell", districts[3], 500),

    new Property("AFI", districts[4], 3300),
    new Property("eMAG", districts[4], 3100),
    new Property("Spitalul Judetean", districts[4], 2900),

    new Property("Dealul Melcilor", districts[5], 1200),
    new Property("Decathlon", districts[5], 900),

    new Property("Postavarul", districts[6], 3500),
    new Property("Belvedere", districts[6], 4500),

    new Property("Gradina Zoologica", districts[7], 1200),
    new Property("Lacul Noua", districts[7], 1500),

    new Property("Carrefour", districts[8], 1000),
    new Property("Jumbo", districts[8], 600),

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