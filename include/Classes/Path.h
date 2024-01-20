#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <string>

enum PathTypes {GUARD_1 = 0, GUARD_2, GUARD_3, 
                COUNTERTERRORIST_1, COUNTERTERRORIST_2, COUNTERTERRORIST_3, COUNTERTERRORIST_4,
                SPECIALFORCE, NROFTYPES};

class Path{
private:
    std::vector<std::tuple<sf::Vector2f, float, std::string>> m_path;
    int m_type;
    sf::Vector2f m_startPosition;
    sf::Vector2f m_currentDirection;
    int m_movingTo;
    std::vector<int> m_movingOrder;

    void initVariables(int type);
    void initPath();
public:
    Path(int type);
    virtual ~Path();

    sf::Vector2f getStartPosition();
    sf::Vector2f getCurrentDirection();
    sf::Vector2f getVertexPosition(int index);
    float getAngle(int index);
    std::string getRotationDirection(int index);
    int getMovingTo();
    
    void changeNextVertex();
};