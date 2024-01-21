#include "Classes/Bullet.h"

// Private functions
sf::Vector2f Bullet::rotatePoint(const sf::Vector2f& point, const sf::Vector2f& center, float angle) {
    ///////////////////////////////////////////////////////////
    // This function rotates given point by an angle 
    // having regard to center position of shape
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //		point - point to rotate
    //		center - position of center of shape 
    //		angle - angle by which point is to be rotated
    // OUTPUT:
    //		vector of two floats(x,y) representing new point
    // REMARKS:

    float radians = angle * 3.14159265f / 180.0f;
    float cosA = std::cos(radians);
    float sinA = std::sin(radians);
    float x = cosA * (point.x - center.x) - sinA * (point.y - center.y) + center.x;
    float y = sinA * (point.x - center.x) + cosA * (point.y - center.y) + center.y;
    return sf::Vector2f(x, y);
}

void Bullet::initShape(sf::Vector2f startPosition, float angle){
    ///////////////////////////////////////////////////////////
    // This function initialize shape 
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //		startPosition - starting position of shape
    //		angle - angle to rotate shape
    // REMARKS:

    m_shape.setFillColor(sf::Color::Yellow);
    m_shape.setSize(sf::Vector2f(20.f, 10.f));
    m_shape.setPosition(startPosition);
    m_shape.setOrigin(sf::Vector2f(0.f, 5.f));
    m_shape.setRotation(angle * 180.f / M_PI);
}

void Bullet::initVariables(float angle){
    ///////////////////////////////////////////////////////////
    // This function initialize private variables 
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //		angle - angle by which points are to be rotated
    // REMARKS:

    m_bulletSpeed = 5.f;
    m_direction = sf::Vector2f(cos(angle), sin(angle));

    // set the position and origin of the m_shape
    sf::Vector2f position = m_shape.getPosition();
    sf::Vector2f origin = m_shape.getOrigin();

    // Calculate the center of the m_shape
    sf::Vector2f center = position + origin;

    // Calculate the rotated points
    sf::Vector2f topLeft = rotatePoint(position, center, m_shape.getRotation());
    sf::Vector2f topRight = rotatePoint(position + sf::Vector2f(m_shape.getSize().x, 0.f), center, m_shape.getRotation());
    sf::Vector2f bottomLeft = rotatePoint(position + sf::Vector2f(0.f, m_shape.getSize().y), center, m_shape.getRotation());
    sf::Vector2f bottomRight = rotatePoint(position + m_shape.getSize(), center, m_shape.getRotation());
    
    // Push back calculated points to vector which stores them
    m_points.push_back(topLeft);
    m_points.push_back(topRight);
    m_points.push_back(bottomLeft);
    m_points.push_back(bottomRight);
    
}

// Constructor and Destructor
Bullet::Bullet(sf::Vector2f startPosition, float angle){
    ///////////////////////////////////////////////////////////
    // This is class constructor
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //		startPosition - starting position of shape
    //		angle - angle by which shape and points are to be rotated
    // REMARKS:

    this->initShape(startPosition, angle);
    this->initVariables(angle);
}

Bullet::~Bullet(){

}


// Accessors
///////////////////////////////////////////////////////////
// This functions access private variebles of class
///////////////////////////////////////////////////////////
std::vector<sf::Vector2f> Bullet::getPoints(){
    return m_points;
}

sf::Vector2f Bullet::getDirection(){
    return m_direction;
}

sf::Vector2f Bullet::getPosition(){
    return m_shape.getPosition();
}

sf::FloatRect Bullet::getBounds(){
    return m_shape.getGlobalBounds();
}

float Bullet::getHeight(){
    return m_shape.getLocalBounds().height;
}

float Bullet::getWidth(){
    return m_shape.getLocalBounds().width;
}

void Bullet::move(){
    ///////////////////////////////////////////////////////////
    // This function moves shape
    ///////////////////////////////////////////////////////////
    //		
    // OUTPUT:
    //		shape and points are moved by given vector of two floats
    // REMARKS:

    // Move shape
    m_shape.move(m_direction.x * m_bulletSpeed, m_direction.y * m_bulletSpeed);

    //Move points
    for(auto &point : m_points){
        point += sf::Vector2f(m_direction.x * m_bulletSpeed, m_direction.y * m_bulletSpeed);
    }
}

void Bullet::update(){
    ///////////////////////////////////////////////////////////
    // This function updates bullet, calls move function
    ///////////////////////////////////////////////////////////
    this->move();
}

void Bullet::render(sf::RenderTarget& target){
    ///////////////////////////////////////////////////////////
    // This function renders shape to given target
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //		target - object to render to

    target.draw(m_shape);
}