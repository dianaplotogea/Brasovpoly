#ifndef CLOSE_BUTTON_HANDLER_H
#define CLOSE_BUTTON_HANDLER_H

#include <SFML/Graphics.hpp>

class CloseButtonHandler
{
public:
    void createCloseButton();
    void closePlayerSetupMenu(sf::RenderWindow& window);
private:
    int closeButtonSize = 45;
    int closeButtonPadding = 30;

    sf::Texture closeButtonTexture;
};



#endif