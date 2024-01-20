#pragma once

#include <SFML/Graphics.hpp>

class Star{
private:
    sf::ConvexShape m_shape;
    void initShape(sf::Vector2f startPosition);
public:
    Star(sf::Vector2f startPosition);
    virtual ~Star();

    sf::FloatRect getBounds();

    void update();
    void render(sf::RenderTarget& target);
};