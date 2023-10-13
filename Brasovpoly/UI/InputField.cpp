#include "InputField.h"
#include "UIContainer.h"

InputField::InputField(UIContainer& uiContainer, float x, float y, float width, float height, sf::Font& font) : UIElement(uiContainer), text(), box(),
    selected(false)
{
    text.setFont(font);
    text.setCharacterSize(24);
    text.setPosition(x, y);
    text.setFillColor(sf::Color::Black);
        
    box.setPosition(x, y);
    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(sf::Color::White);
}

void InputField::draw(sf::RenderWindow& window)
{
    if (visible)
    {
        window.draw(box);
        window.draw(text);
    }
}

void InputField::setSelected(bool isSelected)
{
    selected = isSelected;
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
    if (unicode < 128 && unicode != 8)
    {
        inputString += static_cast<char>(unicode);
    }
    else if (unicode == 8 && !inputString.empty()) // Handle backspace
    {  
        inputString.pop_back();
    }
    text.setString(inputString);
    return inputString;
}

bool InputField::operator<(const InputField& other) const {
    return inputText.getString() < other.inputText.getString();
}

