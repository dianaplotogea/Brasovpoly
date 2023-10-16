#include <iostream>
#include <thread>
#include "TimeHandler.h"
#include "../Globals.h"
#include "../UI/UIText.h"

int inGameClockTextPositionY = 25;
int inGameClockTextPaddingX = 80;
int inGameClockTextCharacterSize = 40;

void startInGameClock()
{
    shouldInGameClockWork = true;
    std::thread timerThread(displayTime);
    timerThread.detach(); // Allows the thread to execute independently from the thread object, making it 'daemon-like'
}

void displayTime()
{
    playingTimeClock->restart();
    while(shouldInGameClockWork)
    {
        sf::Time elapsed = playingTimeClock->getElapsedTime();

        int totalSeconds = static_cast<int>(elapsed.asSeconds());

        int hours = totalSeconds / 3600;
        totalSeconds %= 3600;

        int minutes = totalSeconds / 60;
        totalSeconds %= 60;

        int seconds = totalSeconds;
        std::string inGameClockTextString = "";
        if(hours > 0)
        {
            inGameClockTextString += hours < 10 ? "0" : "";
            inGameClockTextString += std::to_string(hours) + "h ";  
        }
        if(minutes > 0)
        {
            inGameClockTextString += minutes < 10 ? "0" : "";
            inGameClockTextString += std::to_string(minutes) + "m ";
        }
        inGameClockTextString += seconds < 10 ? "0" : "";
        inGameClockTextString += std::to_string(seconds) + "s";
        
        inGameClockText->setString(inGameClockTextString);
        inGameClockText->setPosition(sf::Vector2f(windowWidth - inGameClockTextPaddingX - inGameClockText->getLocalBounds().width, inGameClockTextPositionY));
        inGameClockText->setCharacterSize(inGameClockTextCharacterSize); // It has to be set here, if it's set when the text is created, sometimes the letter s becomes really small
        if(totalSeconds >=1)
        {
            inGameClockText->show(); // It has to be shown only when more than one seconds have passed, otherwise it won't be at the correct position
        }
        
        sf::sleep(sf::seconds(1));
    }
}