#pragma once

#include <SFML/Graphics.hpp>
#include <limits>
#include <cmath>
#include <iostream>
class Ray{
private:
    sf::Vector2f m_startPoint;
    sf::Vector2f m_endPoint;
    sf::Vector2f m_direction;
    float m_defaultRayLength;
    float m_rayLength;
    sf::Vertex m_ray[2];
    void initVariables(sf::Vector2f startPoint, sf::Vector2f direction, sf::Color color, float length);
public:
    Ray(sf::Vector2f startPoint, sf::Vector2f direction, sf::Color color, float length);
    virtual ~Ray();

    sf::Vertex getRay();
    float getRayLength();
    sf::Vector2f getStartPoint();
    sf::Vector2f getEndPoint();
    sf::Vector2f getDirection();

    void setRayLength(float length);
    void rotate(float angle);
    void collisionWalls(sf::VertexArray& walls);
    void update(sf::VertexArray& walls, sf::Vector2f playerPosition, float angle);
    void render(sf::RenderTarget& target);
};