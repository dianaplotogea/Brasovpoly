#include <iostream>
#include "GameOverHandler.h"
#include "../Globals.h"
#include "../UI/UIText.h"


void GameOverHandler::gameOver()
{
    globals.getInGameScene().hideAll();
    globals.getGameOverText()->setVisible(true);
    globals.getPlayersInWinningOrder().insert(globals.getPlayersInWinningOrder().begin(), globals.getPlayers()[0]); // Adding the winner
    for(int i=0;i<globals.getPlayersInWinningOrder().size();i++)
    {
        UIText* leaderBoardNameText = new UIText(globals.getInGameScene(), globals.getGlobalFont(), leaderBoardCharacterSize, std::to_string(i+1) + ". " + globals.getPlayersInWinningOrder()[i]->getName(), globals.getPlayersInWinningOrder()[i]->getColor());
        leaderBoardNameText->setPosition(sf::Vector2f(Globals::windowWidth/2 - leaderBoardNameText->getLocalBounds().width/2, leaderBoardNameTextInitialPositionY + i*distanceBetweenLeaderBoardNameTexts));
        globals.getLeaderBoardNameTexts().push_back(leaderBoardNameText);
        globals.getInGameSceneUIElementsThatMustBeDeleted().push_back(leaderBoardNameText);
    }
    globals.getPlayersInWinningOrder().clear();
    globals.setShouldInGameClockWork(false);
    globals.getGameOverPlayingTimeText()->setVisible(true);
    globals.getGameOverPlayingTimeText()->setString("Playing time: " + globals.getInGameClockText()->getString());
    globals.getGameOverPlayingTimeText()->setPosition(sf::Vector2f(Globals::windowWidth/2 - globals.getGameOverPlayingTimeText()->getLocalBounds().width/2, gameOverPlayingTimeTextPositionY));

}