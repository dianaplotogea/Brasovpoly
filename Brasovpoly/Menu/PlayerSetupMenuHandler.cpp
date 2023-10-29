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



void PlayerSetupMenuHandler::createPlayerSetupMenu(int numberOfPlayers)
{
    globals.setCurrentState(Globals::GameState::PlayerSetup);
    int colorIndex = globals.getPlayerColors().size()-1;
    for(int i=2;i<numberOfPlayers+3;i++)
    {
        float positionX = distanceBetweenElementsX - inputFieldWidth + distanceBetweenElementsX * (i-2);

        UIText* playerIndexText = new UIText(globals.getPlayerSetupMenu(), globals.getGlobalFont(), 24, "Player" + std::to_string(i-1), globals.getPlayerColors()[colorIndex]); // TODO: Magic number
        playerIndexText->setPosition(sf::Vector2f(positionX + (inputFieldWidth - playerIndexText->getLocalBounds().width)/2, textPositionY));

        InputField* inputField = new InputField(globals.getPlayerSetupMenu(), positionX, inputFieldPositionY, inputFieldWidth, inputFieldHeight, *globals.getGlobalFont());

        Button* colorButton = new Button(globals.getPlayerSetupMenu(), positionX + (inputFieldWidth - colorButtonWidth)/2, colorButtonPositionY, colorButtonWidth, colorButtonHeight, globals.getGlobalFont(), "Change color", globals.getButtonColor(), Globals::buttonBorderThickness, globals.getButtonBorderColor());
        globals.getOutlineColorHoverButtons().push_back(colorButton);
        
        Player* player = new Player(i-1, playerIndexText, inputField, colorButton, globals.getPlayerColors()[colorIndex--]);
        globals.getPlayers().push_back(player);
    }

    inputText.setFont(*globals.getGlobalFont());
    inputText.setCharacterSize(24);
    inputText.setPosition(inputTextPosition, inputTextPosition);
    inputText.setString(inputString);
}

void PlayerSetupMenuHandler::selectPlayerSetupMenuInput(sf::RenderWindow& window, sf::Event event)
{
    for (Player* player : globals.getPlayers())
    {
        player->getInputField()->setSelected(player->getInputField()->getGlobalBounds().contains(window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y})));
    }
}

void PlayerSetupMenuHandler::handleEnteredTextSelectPlayerSetupMenu(sf::Event event)
{
    for(Player* player : globals.getPlayers())
    {
        if(player->getInputField()->isSelected())
        {
            player->setName(player->getInputField()->handleTextEntered(event.text.unicode));
            activateStartGameButtonIfAllPlayersAreSet();
        }
    }
}

void PlayerSetupMenuHandler::activateStartGameButtonIfAllPlayersAreSet()
{
    std::unordered_set<std::string> colorSet;
    std::unordered_set<std::string> nameSet;
    for (Player* player : globals.getPlayers())
    {
        if (player->getName().empty())
        {
            globals.getStartGameButton()->setVisible(false);
            return;
        }

        if (player->getColor() == sf::Color::Black)
        {
            globals.getStartGameButton()->setVisible(false);
            return;
        }

        std::string colorString = std::to_string(player->getColor().r) + "," + std::to_string(player->getColor().g) + "," + std::to_string(player->getColor().b) + "," + std::to_string(player->getColor().a);

        auto [nameIter, nameInserted] = nameSet.insert(player->getName());
        auto [colorIter, colorInserted] = colorSet.insert(colorString);

        if (!nameInserted || !colorInserted) // If insertion failed for either name or color, they are not unique
        {
            globals.getStartGameButton()->setVisible(false);
            globals.setShouldStartGameButtonBeActivated(false);
            return;
        }        
    }
    if(globals.getCurrentState() == Globals::GameState::PlayerSetup)
    {
        globals.getStartGameButton()->setVisible(true);
    }
    else if(globals.getCurrentState() == Globals::GameState::PlayerColorSelection)
    {
        globals.setShouldStartGameButtonBeActivated(true);
    }
    
}

void PlayerSetupMenuHandler::createStartGameButton()
{
    globals.setStartGameButton
    (
        new Button
        (
            globals.getPlayerSetupMenu(),
            Globals::windowWidth/2 - startGameButtonWidth/2,
            Globals::windowHeight - startGameButtonDistanceFromBottom - startGameButtonHeight/2,
            startGameButtonWidth,
            startGameButtonHeight,
            globals.getGlobalFont(),
            "Start game",
            globals.getButtonColor(),
            Globals::buttonBorderThickness,
            globals.getButtonBorderColor()
        )
    );
    globals.getOutlineColorHoverButtons().push_back(globals.getStartGameButton());
    globals.getStartGameButton()->setVisible(false);
}