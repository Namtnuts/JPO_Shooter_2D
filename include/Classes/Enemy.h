#pragma once

#include "Classes/Ray.h"
#include "Classes/Path.h"
#include <memory>
#include <math.h>

class Enemy{
protected:
    sf::CircleShape m_shape;

    float m_movementSpeed;
    float m_fov;
    float m_offset;
    int m_healthPoints;
    bool m_playerDetected;
    sf::Vector2f m_direction;
    std::vector<std::shared_ptr<Ray>> m_rays;
    std::shared_ptr<Path> m_path;

    virtual void initVariables() = 0;
    virtual void initShape() = 0;
    virtual void initRays() = 0;
    virtual void initPath(int type) = 0;
public:
    Enemy();
    virtual ~Enemy();

    sf::FloatRect getBounds();
    std::vector<std::shared_ptr<Ray>> getRays();
    bool getIsPlayerDetected();

    sf::Vector2f proj(sf::Vector2f A, sf::Vector2f B);
    float hypot2(sf::Vector2f A, sf::Vector2f B);

    bool isPlayerDetected(sf::Vector2f playerPosition, sf::Vector2f rayStart, sf::Vector2f rayEnd, float playerRadius);
    bool isDead();
    void gotShot();
    void move();
    void rotate(std::string rotationDirection);
    void updateRays(sf::VertexArray& walls, sf::Vector2f playerPosition, float playerRadius);
    void update(sf::VertexArray& walls, sf::Vector2f playerPosition, float playerRadius);
    void renderRays(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};