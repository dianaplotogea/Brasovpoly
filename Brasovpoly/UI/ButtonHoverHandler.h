#ifndef BUTTON_EVENT_HANDLER_H
#define BUTTON_EVENT_HANDLER_H

#include <SFML/Graphics.hpp>

class ButtonHoverHandler
{
public:
    void buttonHover(sf::RenderWindow& window);
private:
    sf::Color buttonHoverColor = {128, 128, 128};
};

#endif