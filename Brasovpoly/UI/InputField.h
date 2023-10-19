#ifndef UIINPUT_TEXT_H
#define UIINPUT_TEXT_H

#include "UIElement.h"
#include "UIRectangleShape.h"

class InputField : public UIElement
{
public:
    InputField(UIContainer& uiContainer, float x, float y, float width, float height, sf::Font& font);
    void draw(sf::RenderWindow& window) override;
    void setSelected(bool isSelected);
    static void displayCursor(InputField* inputField); // It must be static in order to put it on a different thread as a member function
    bool isSelected() const;
    std::string handleTextEntered(sf::Uint32 unicode);
    sf::FloatRect getGlobalBounds();
    bool operator<(const InputField& other) const;

private:
    bool selected = false;
    bool isTicking = false;
    sf::Text inputText;
    sf::Text text;
    sf::RectangleShape box;
    UIRectangleShape* cursor;
    sf::Clock cursorClock;
    
};

#endif