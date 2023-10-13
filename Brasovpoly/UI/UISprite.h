#ifndef UI_SPRITE_H
#define UI_SPRITE_H

#include "UIElement.h"

class UISprite : public UIElement
{
public:
    UISprite(UIContainer& uiContainer, sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& scale);
    void setPosition(const sf::Vector2f& position);
    void setSize(const sf::Vector2f& size, const sf::Vector2u& textureSize);
    void draw(sf::RenderWindow& window) override;

private:
    sf::Sprite sprite;

};

#endif