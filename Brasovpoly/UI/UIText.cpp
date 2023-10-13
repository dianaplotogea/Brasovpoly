#include "UIText.h"
#include "UIContainer.h"

UIText::UIText(UIContainer& uiContainer, sf::Font* font, int characterSize, const std::string& textStr, sf::Color color) : UIElement(uiContainer)
{
    text.setFont(*font);
    text.setString(textStr);
    text.setCharacterSize(characterSize);
    text.setFillColor(color);
}

sf::FloatRect UIText::getLocalBounds() const
{
    return text.getLocalBounds();
}

void UIText::setOrigin(float x, float y)
{
    text.setOrigin(x, y);
}

void UIText::draw(sf::RenderWindow& window)
{
    if (visible)
    {
        window.draw(text);
    }
}

void UIText::setString(const std::string& textStr)
{
    text.setString(textStr);
}

void UIText::setPosition(const sf::Vector2f& position)
{
    text.setPosition(position);
}

void UIText::setCharacterSize(unsigned int size)
{
    text.setCharacterSize(size);
}

void UIText::setColor(const sf::Color& color)
{
    text.setFillColor(color);
}

sf::FloatRect UIText::getLocalBounds()
{
    return text.getLocalBounds();
}
