#include "PlayerColorSelector.h"
#include <iostream>
#include "Globals.h"
#include "Player.h"
#include "UI/Button.h"
#include "UI/UIText.h"
#include "PlayerSetupMenuHandler.h"

int numberOfColumns = 3;
int distanceBetweenElements = 100;
int colorSelectorButtonWidth = 100;
int colorSelectorButtonHeight = 100;
int colorSelectorButtonPositionX = (windowWidth - numberOfColumns * colorSelectorButtonWidth - (numberOfColumns-1) * distanceBetweenElements)/2;
int colorSelectorButtonInitialPositionY = 100;
int colorSelectorButtonPositionY = 100;

std::vector<sf::Color> colors =
{
    {sf::Color::White},
    {sf::Color::Red},
    {sf::Color::Green},
    {sf::Color::Blue},
    {sf::Color::Yellow},
    {sf::Color::Magenta},
    {sf::Color::Cyan},
    {255, 165, 0}, // Orange
    {153, 101, 21}  // Brown
};

std::map<Button*, sf::Color> colorSelectorButtonsAndColors;

UIText* playerColorSelectorText;

Player* currentPlayer;

void createColorSelectorMenu()
{
    playerColorSelectorText = new UIText(playerColorSelectorMenu);

    int numberOfColors = colors.size();
    while(numberOfColors !=0)
    {
        if(numberOfColors < numberOfColumns)
        {
            numberOfColumns = numberOfColors;
        }
        int currentColorSelectorButtonPositionX = colorSelectorButtonPositionX;
        for(int i=0;i<numberOfColumns;i++)
        {
            Button* colorSelectorButton = new Button(playerColorSelectorMenu, currentColorSelectorButtonPositionX, colorSelectorButtonInitialPositionY + colorSelectorButtonPositionY, colorSelectorButtonWidth, colorSelectorButtonHeight, &font, "", colors[numberOfColors-1]);
            colorSelectorButtonsAndColors.insert(std::make_pair(colorSelectorButton, colors[numberOfColors-1]));
            currentColorSelectorButtonPositionX += distanceBetweenElements + colorSelectorButtonWidth;
            numberOfColors--;
        }
        colorSelectorButtonPositionY += distanceBetweenElements + colorSelectorButtonHeight;
    }
    playerColorSelectorMenu.hideAll();

}

void colorButtonEventHandler(sf::RenderWindow& window)
{
    for(Player* player : players)
    {
        if(player->colorButton->isMouseOver(window))
        {
            playerSetupMenu.hideAll();
            playerColorSelectorMenu.showAll();
            currentState = GameState::PlayerColorSelection;
            playerColorSelectorText->setString("Select color for Player" + std::to_string(player->count));
            playerColorSelectorText->setPosition(sf::Vector2f(windowWidth/2, 50));
            sf::FloatRect playerColorSelectorTextRect = playerColorSelectorText->getLocalBounds();
            playerColorSelectorText->setOrigin(playerColorSelectorTextRect.width/2.0f, playerColorSelectorTextRect.height/2.0f);
            currentPlayer = player;
        }
    }
}

void colorSelectorButtonEventHandler(sf::RenderWindow& window)
{
    for(const auto& colorSelectorButtonsAndColorsPair : colorSelectorButtonsAndColors)
    {
        if(colorSelectorButtonsAndColorsPair.first->isMouseOver(window))
        {
            currentPlayer->color = colorSelectorButtonsAndColorsPair.second;
            currentPlayer->playerIndexText->setColor(colorSelectorButtonsAndColorsPair.second);
            std::cout << "Color set for " << currentPlayer->count << std::endl; 
            activateStartGameButtonIfAllPlayersAreSet();
        }
    }
}