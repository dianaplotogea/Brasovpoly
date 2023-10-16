#include <iostream>
#include <string>
#include <unordered_set>
#include "../UI/UIText.h"
#include "../UI/Button.h"
#include "../Globals.h"
#include "../UI/UISprite.h"
#include "../UI/InputField.h"
#include "PlayerSetupMenuHandler.h"
#include "../Player.h"

int initialPositionX = 0;
int distanceBetweenElementsX = 250;
int textPositionY = 150;
int inputFieldPositionY = 250;
int colorButtonPositionY = 350;
int colorButtonWidth = 150;
int colorButtonHeight = 50;
int inputTextPosition = 50;

int inputFieldWidth = 220;
int inputFieldHeight = 24;

int startGameButtonWidth = 200;
int startGameButtonHeight = 50;
int startGameButtonDistanceFromBottom = 100;

std::string inputString;

sf::Text inputText;

void createPlayerSetupMenu(int numberOfPlayers)
{
    currentState = GameState::PlayerSetup;
    int colorIndex = colors.size()-1;
    for(int i=2;i<numberOfPlayers+3;i++)
    {
        float positionX = distanceBetweenElementsX - inputFieldWidth + distanceBetweenElementsX * (i-2);

        UIText* playerIndexText = new UIText(playerSetupMenu, &font, 24, "Player" + std::to_string(i-1), colors[colorIndex]); // TODO: Magic number
        playerIndexText->setPosition(sf::Vector2f(positionX + (inputFieldWidth - playerIndexText->getLocalBounds().width)/2, textPositionY));

        InputField* inputField = new InputField(playerSetupMenu, positionX, inputFieldPositionY, inputFieldWidth, inputFieldHeight, font);

        Button* colorButton = new Button(playerSetupMenu, positionX + (inputFieldWidth - colorButtonWidth)/2, colorButtonPositionY, colorButtonWidth, colorButtonHeight, &font, "Change color", buttonColor, buttonBorderThickness, buttonBorderColor);
        outlineColorHoverButtons.push_back(colorButton);
        
        Player* player = new Player(i-1, playerIndexText, inputField, colorButton, colors[colorIndex--]);
        players.push_back(player);
    }

    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setPosition(inputTextPosition, inputTextPosition);
    inputText.setString(inputString);
}

void selectPlayerSetupMenuInput(sf::RenderWindow& window, sf::Event event)
{
    for (Player* player : players)
    {
        player->inputField->setSelected(player->inputField->getGlobalBounds().contains(window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y})));
    }
}

void handleEnteredTextSelectPlayerSetupMenu(sf::Event event)
{
    for(Player* player : players)
    {
        if(player->inputField->isSelected())
        {
            player->name = player->inputField->handleTextEntered(event.text.unicode);
            std::cout << player->name << std::endl;
            activateStartGameButtonIfAllPlayersAreSet();
        }
    }
}

void activateStartGameButtonIfAllPlayersAreSet()
{
    std::unordered_set<std::string> colorSet;
    std::unordered_set<std::string> nameSet;
    for (Player* player : players)
    {
        if (player->name.empty())
        {
            startGameButton->hide();
            return;
        }

        if (player->color == sf::Color::Black)
        {
            startGameButton->hide();
            return;
        }

        std::string colorString = std::to_string(player->color.r) + "," + std::to_string(player->color.g) + "," + std::to_string(player->color.b) + "," + std::to_string(player->color.a);

        auto [nameIter, nameInserted] = nameSet.insert(player->name);
        auto [colorIter, colorInserted] = colorSet.insert(colorString);

        if (!nameInserted || !colorInserted) // If insertion failed for either name or color, they are not unique
        {
            startGameButton->hide();
            shouldStartGameButtonBeActivated = false;
            return;
        }        
    }
    if(currentState == GameState::PlayerSetup)
    {
        startGameButton->show();
    }
    else if(currentState == GameState::PlayerColorSelection)
    {
        shouldStartGameButtonBeActivated = true;
    }
    
}

void createStartGameButton()
{
    startGameButton = new Button
    (
        playerSetupMenu,
        windowWidth/2 - startGameButtonWidth/2,
        windowHeight - startGameButtonDistanceFromBottom - startGameButtonHeight/2,
        startGameButtonWidth,
        startGameButtonHeight,
        &font,
        "Start game",
        buttonColor,
        buttonBorderThickness,
        buttonBorderColor
    );
    outlineColorHoverButtons.push_back(startGameButton);
    startGameButton->hide();
}