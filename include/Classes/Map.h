#pragma once

#include <SFML/Graphics.hpp>

class Map{
private:
    sf::VertexArray m_walls;
public:
    Map();
    virtual ~Map();

    sf::VertexArray getWalls();

    void update();
    void render(sf::RenderTarget& target);
};