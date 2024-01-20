#include "Classes/Counterterrorist.h"

void Counterterrorist::initPath(int type){
    m_path = std::make_shared<Path>(type);
}

void Counterterrorist::initVariables(){
    m_movementSpeed = 1.f;
    m_fov = 90.f;
    m_direction = m_path->getCurrentDirection();
    m_offset = acos((m_direction.x * 1.f) / (sqrt(pow(m_direction.x, 2) + pow(m_direction.y, 2))));
    m_healthPoints = 2;
    m_playerDetected = false;
}

void Counterterrorist::initShape(){
    m_shape.setFillColor(sf::Color(220,20,60));
    m_shape.setRadius(10.f);
    m_shape.setPosition(m_path->getStartPosition() - sf::Vector2f(m_shape.getRadius(), m_shape.getRadius()));
}

void Counterterrorist::initRays(){
    m_offset = (m_direction.y < 0.f) ? m_offset * -1.f : m_offset * 1.f;
    float fov = m_fov * (M_PI / 180.f);
    for(float angle = m_offset - fov / 2; angle < m_offset + fov / 2; angle += 0.01f){
        m_rays.push_back(std::make_shared<Ray>(m_shape.getPosition(), sf::Vector2f(cos(angle), sin(angle)), sf::Color(220,20,60, 255), 100.f));
    }
    for(auto &ray : m_rays){
        ray->setRayLength(125.f);
    }
}

Counterterrorist::Counterterrorist(int type){
    this->initPath(type);
    this->initVariables();
    this->initShape();
    this->initRays();
}

Counterterrorist::~Counterterrorist(){

}