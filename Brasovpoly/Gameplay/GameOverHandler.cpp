#include<iostream>
#include "GameOverHandler.h"
#include "../Globals.h"
#include "../UI/UIText.h"

int leaderBoardCharacterSize = 35;
int leaderBoardNameTextInitialPositionY = 400;
int distanceBetweenLeaderBoardNameTexts = 80;

int gameOverPlayingTimeTextPositionY = 250;

void gameOver()
{
    while(shouldInGameClockWork)
    {
        inGameScene.hideAll();
        gameOverText->show();
        playersInWinningOrder.insert(playersInWinningOrder.begin(), players[0]); // Adding the winner
        for(int i=0;i<playersInWinningOrder.size();i++)
        {
            UIText* leaderBoardNameText = new UIText(inGameScene, &font, leaderBoardCharacterSize, std::to_string(i+1) + ". " + playersInWinningOrder[i]->name, playersInWinningOrder[i]->color);
            leaderBoardNameText->setPosition(sf::Vector2f(windowWidth/2 - leaderBoardNameText->getLocalBounds().width/2, leaderBoardNameTextInitialPositionY + i*distanceBetweenLeaderBoardNameTexts));
            leaderBoardNameTexts.push_back(leaderBoardNameText);
        }
        playersInWinningOrder.clear();
        shouldInGameClockWork = false;
        gameOverPlayingTimeText->show();
        gameOverPlayingTimeText->setString("Playing time: " + inGameClockText->getString());
        gameOverPlayingTimeText->setPosition(sf::Vector2f(windowWidth/2 - gameOverPlayingTimeText->getLocalBounds().width/2, gameOverPlayingTimeTextPositionY));
    }

}