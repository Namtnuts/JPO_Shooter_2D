#include "Classes/Specialforce.h"

// Private functions
void Specialforce::initPath(int type){
    ///////////////////////////////////////////////////////////
    // This function initialize path
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //		type - type of path (defined in Path.h)

    m_path = std::make_shared<Path>(type);
}

void Specialforce::initVariables(){
    ///////////////////////////////////////////////////////////
    // This function initialize private variables 
    ///////////////////////////////////////////////////////////

    m_movementSpeed = 1.5f;
    m_fov = 120.f;

    // Set direction given by path
    m_direction = m_path->getCurrentDirection();

    // Calculate and set offset
    m_offset = acos((m_direction.x * 1.f) / (sqrt(pow(m_direction.x, 2) + pow(m_direction.y, 2))));

    m_healthPoints = 3;
    m_playerDetected = false;
}

void Specialforce::initShape(){
    ///////////////////////////////////////////////////////////
    // This function initialize shape 
    ///////////////////////////////////////////////////////////

    m_shape.setFillColor(sf::Color(134,1,17));
    m_shape.setRadius(10.f);
    m_shape.setPosition(m_path->getStartPosition() - sf::Vector2f(m_shape.getRadius(), m_shape.getRadius()));
}

void Specialforce::initRays(){
    ///////////////////////////////////////////////////////////
    // This function initialize rays
    ///////////////////////////////////////////////////////////

    // Check if direction is lower than 0.f and multiply current offset by right value
    m_offset = (m_direction.y < 0.f) ? m_offset * -1.f : m_offset * 1.f;
    float fov = m_fov * (M_PI / 180.f);

    // Intialize rays regadring offset and fov
    for(float angle = m_offset - fov / 2; angle < m_offset + fov / 2; angle += 0.01f){
        m_rays.push_back(std::make_shared<Ray>(m_shape.getPosition(), sf::Vector2f(cos(angle), sin(angle)), sf::Color(134,1,17, 255), 300.f));
    }

    // Set rays length
    for(auto &ray : m_rays){
        ray->setRayLength(500.f);
    }
}

// Constructor and Destructor
Specialforce::Specialforce(int type){
    ///////////////////////////////////////////////////////////
    // This is class constructor
    ///////////////////////////////////////////////////////////
    
    this->initPath(type);
    this->initVariables();
    this->initShape();
    this->initRays();
}

Specialforce::~Specialforce(){

}