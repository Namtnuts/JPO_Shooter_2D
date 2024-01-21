#pragma once

#include <SFML/Graphics.hpp>
#include "Classes/Ray.h"
#include <vector>
#include <limits>
#include <math.h>
#include <cmath>
#include <memory>

class Player{
private:
    sf::CircleShape m_shape;

    float m_movementSpeed;
    float m_fov;
    float m_offset;
    sf::Vector2f m_playerDirection;
    std::vector<std::shared_ptr<Ray>> m_rays;
    std::unique_ptr<Ray> m_crosshair;

    float m_shootCooldown;
    float m_shootCooldownMax;

    void initVariables();
    void initShape();
    void initRays();
    void initCrosshair();

public:
    Player();
    virtual ~Player();

    void setPosition(sf::Vector2f position);

    sf::Vector2f getPosition();
    float getRadius();
    sf::Vector2f getDirection();
    sf::FloatRect getGlobalBounds();
    std::vector<std::shared_ptr<Ray>> getRays();

    bool checkPlayerMapIntersect(sf::Vector2f moveDirection);
    const bool canshoot();
    void updateInput();
    void updateRays(sf::VertexArray& walls, sf::Vector2i mousePosition);
    void updateShoot();
    void update(sf::VertexArray& walls, sf::Vector2i mousePosition);
    void renderRays(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};