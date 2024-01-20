#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class Bullet{
private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_direction;
    float m_bulletSpeed;
    std::vector<sf::Vector2f> m_points;

    sf::Vector2f rotatePoint(const sf::Vector2f& point, const sf::Vector2f& center, float angle);
    void initShape(sf::Vector2f startPosition, float angle);
    void initVariables(float angle);

public:
    Bullet(sf::Vector2f startPosition, float angle);
    virtual ~Bullet();

    std::vector<sf::Vector2f> getPoints();
    sf::Vector2f getDirection();
    sf::Vector2f getOffsetPosition();
    sf::Vector2f getPosition();
    sf::FloatRect getBounds();
    float getHeight();
    float getWidth();

    void move();
    void update();
    void render(sf::RenderTarget& target);
};