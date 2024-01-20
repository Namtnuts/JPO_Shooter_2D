#include "Classes/Star.h"

void Star::initShape(sf::Vector2f startPosition){
    m_shape.setPointCount(8);
    m_shape.setPoint(0, sf::Vector2f(20.f, 0.f) + startPosition);
    m_shape.setPoint(1, sf::Vector2f(25.f, 15.f) + startPosition);
    m_shape.setPoint(2, sf::Vector2f(40.f, 20.f) + startPosition);
    m_shape.setPoint(3, sf::Vector2f(25.f, 25.f) + startPosition);
    m_shape.setPoint(4, sf::Vector2f(20.f, 40.f) + startPosition);
    m_shape.setPoint(5, sf::Vector2f(15.f, 25.f) + startPosition);
    m_shape.setPoint(6, sf::Vector2f(0.f, 20.f) + startPosition);
    m_shape.setPoint(7, sf::Vector2f(15.f, 15.f) + startPosition);
    m_shape.setFillColor(sf::Color::Yellow);
}

Star::Star(sf::Vector2f startPosition){
    this->initShape(startPosition);
}

Star::~Star(){

}

sf::FloatRect Star::getBounds(){
    return m_shape.getGlobalBounds();
}

void Star::update(){

}

void Star::render(sf::RenderTarget& target){
    target.draw(m_shape);
}