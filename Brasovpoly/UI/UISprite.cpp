#include "UISprite.h"
#include "UIContainer.h"
 
UISprite:: UISprite(UIContainer& uiContainer, sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size) : UIElement(uiContainer)
{
    sprite.setTexture(*texture);
    sprite.setPosition(position);
    setSize(size, texture->getSize());
}

void UISprite::setPosition(const sf::Vector2f& position)
{
    sprite.setPosition(position);
}

void UISprite::setSize(const sf::Vector2f& size, const sf::Vector2u& textureSize)
{
    sprite.setScale(size.x/textureSize.x, size.y/textureSize.y);
}

void UISprite::setColor(sf::Color color)
{
    sprite.setColor(color);
}

void UISprite::draw(sf::RenderWindow& window)
{
    if (isVisible())
    {
        window.draw(sprite);
    }
}