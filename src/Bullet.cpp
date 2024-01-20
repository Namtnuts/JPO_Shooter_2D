#include "Classes/Bullet.h"

sf::Vector2f Bullet::rotatePoint(const sf::Vector2f& point, const sf::Vector2f& center, float angle) {
    float radians = angle * 3.14159265f / 180.0f;
    float cosA = std::cos(radians);
    float sinA = std::sin(radians);
    float x = cosA * (point.x - center.x) - sinA * (point.y - center.y) + center.x;
    float y = sinA * (point.x - center.x) + cosA * (point.y - center.y) + center.y;
    return sf::Vector2f(x, y);
}

void Bullet::initShape(sf::Vector2f startPosition, float angle){
    m_shape.setFillColor(sf::Color::Yellow);
    m_shape.setSize(sf::Vector2f(20.f, 10.f));
    m_shape.setPosition(startPosition);
    m_shape.setOrigin(sf::Vector2f(0.f, 5.f));
    m_shape.setRotation(angle * 180.f / M_PI);
}

void Bullet::initVariables(float angle){
    m_bulletSpeed = 5.f;
    m_direction = sf::Vector2f(cos(angle), sin(angle));
    // Get the position and origin of the m_shape
    sf::Vector2f position = m_shape.getPosition();
    sf::Vector2f origin = m_shape.getOrigin();

    // Calculate the center of the m_shape
    sf::Vector2f center = position + origin;

    // Calculate the rotated points
    sf::Vector2f topLeft = rotatePoint(position, center, m_shape.getRotation());
    sf::Vector2f topRight = rotatePoint(position + sf::Vector2f(m_shape.getSize().x, 0.f), center, m_shape.getRotation());
    sf::Vector2f bottomLeft = rotatePoint(position + sf::Vector2f(0.f, m_shape.getSize().y), center, m_shape.getRotation());
    sf::Vector2f bottomRight = rotatePoint(position + m_shape.getSize(), center, m_shape.getRotation());
    
    m_points.push_back(topLeft);
    m_points.push_back(topRight);
    m_points.push_back(bottomLeft);
    m_points.push_back(bottomRight);
    
}

Bullet::Bullet(sf::Vector2f startPosition, float angle){
    this->initShape(startPosition, angle);
    this->initVariables(angle);
}

Bullet::~Bullet(){

}

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
    m_shape.move(m_direction.x * m_bulletSpeed, m_direction.y * m_bulletSpeed);
    for(auto &point : m_points){
        point += sf::Vector2f(m_direction.x * m_bulletSpeed, m_direction.y * m_bulletSpeed);
    }
}

void Bullet::update(){
    this->move();
}

void Bullet::render(sf::RenderTarget& target){
    target.draw(m_shape);
}