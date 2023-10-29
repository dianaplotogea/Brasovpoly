#ifndef GAMEOVER_HANDLER_H
#define GAMEOVER_HANDLER_H

class GameOverHandler
{
public:
    void gameOver();
private:
    int leaderBoardCharacterSize = 35;
    int leaderBoardNameTextInitialPositionY = 400;
    int distanceBetweenLeaderBoardNameTexts = 80;

    int gameOverPlayingTimeTextPositionY = 250;
};



#endif