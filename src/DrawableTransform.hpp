#pragma once
#include <SFML/Graphics.hpp>

// @TODO Currently not used

class DrawableTransform : public sf::Transformable, public sf::Drawable
{
private:
    std::vector<std::unique_ptr<sf::Drawable>> drawables;
public:
    virtual ~DrawableTransform() = default;

protected:
    // Pure virtual override from sf::Drawable keeps this class strictly abstract
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};