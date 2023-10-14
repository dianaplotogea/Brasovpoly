#include "TimeHandler.h"

#include <SFML/System/Clock.hpp>
#include <iostream>
#include <iomanip>
#include <thread>
#include "../Globals.h"
#include "../UI/UIText.h"

int inGameClockTextPositionY = 25;
int inGameClockTextPaddingX = 80;

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

        sf::sleep(sf::seconds(1));
    }
}