#pragma once

#include <SFML/Graphics.hpp>

class FinishStar{
private:
    sf::ConvexShape m_shape;
    void initShape(sf::Vector2f startPosition);
public:
    FinishStar(sf::Vector2f startPosition);
    virtual ~FinishStar();

    sf::FloatRect getBounds();

    void update();
    void render(sf::RenderTarget& target);
};