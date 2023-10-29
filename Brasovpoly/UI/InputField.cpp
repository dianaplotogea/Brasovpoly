#include <thread>
#include <iostream>
#include "InputField.h"
#include "UIContainer.h"



InputField::InputField(UIContainer& uiContainer, float x, float y, float width, float height, sf::Font& font) : UIElement(uiContainer)
{
    text.setFont(font);
    text.setCharacterSize(24);
    text.setPosition(x, y);
    text.setFillColor(sf::Color::Black);
        
    box.setPosition(x, y);
    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(sf::Color::White);

    cursor = new UIRectangleShape(uiContainer, sf::Vector2f(x + distanceBetweenCursorAndText, box.getPosition().y + (box.getSize().y-box.getSize().y*boxHeightToCursorHeightRatio)/2 ), sf::Vector2f(cursorWidth, height*boxHeightToCursorHeightRatio), sf::Color::Black);
    cursor->setVisible(false);
}

void InputField::draw(sf::RenderWindow& window)
{
    if (isVisible())
    {
        window.draw(box);
        window.draw(text);
    }
}

void InputField::setSelected(bool isSelected)
{
    if(isSelected)
    {
        if(!isTicking)
        {
            std::thread timerThread(displayCursor, this);
            timerThread.detach();
            isTicking = true;
        }

    }
    else
    {
        isTicking = false;
        cursor->setVisible(false);
    }
    selected = isSelected;
}

void InputField::displayCursor(InputField* inputField)
{
    inputField->cursorClock.restart();
    while(inputField->selected)
    {
        inputField->cursor->setVisible(!inputField->cursor->isVisible());
        inputField->cursor->setPosition
        (
            sf::Vector2f
            (
                inputField->box.getPosition().x + inputField->distanceBetweenCursorAndText + inputField->text.getLocalBounds().width,
                inputField->box.getPosition().y + (inputField->box.getSize().y-(inputField->box.getSize().y*inputField->boxHeightToCursorHeightRatio))/2 
            )
        );
        sf::sleep(sf::seconds(inputField->cursorTickFrequency));
    }
}

bool InputField::isSelected() const
{
    return selected;
}

sf::FloatRect InputField::getGlobalBounds()
{
    return box.getGlobalBounds();
}

std::string InputField::handleTextEntered(sf::Uint32 unicode)
{
    std::string inputString = text.getString();
    if(unicode != 8 && unicode != 32) // If it's not backspace and not space
    {
        inputString += static_cast<char>(unicode);
        
    }
    else if(unicode == 8 && !inputString.empty()) // Is it's backspace
    {  
        inputString.pop_back();
    }
    text.setString(inputString);
    cursor->setPosition(sf::Vector2f(box.getPosition().x + distanceBetweenCursorAndText + text.getLocalBounds().width,  box.getPosition().y + (box.getSize().y-box.getSize().y*boxHeightToCursorHeightRatio)/2 ) );
    return inputString;
}

bool InputField::operator<(const InputField& other) const
{
    return inputText.getString() < other.inputText.getString();
}

