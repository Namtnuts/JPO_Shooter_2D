#include "Classes/FinishStar.h"

void FinishStar::initShape(sf::Vector2f startPosition){
    m_shape.setPointCount(8);
    m_shape.setPoint(0, sf::Vector2f(40.f, 0.f) + startPosition);
    m_shape.setPoint(1, sf::Vector2f(50.f, 30.f) + startPosition);
    m_shape.setPoint(2, sf::Vector2f(80.f, 40.f) + startPosition);
    m_shape.setPoint(3, sf::Vector2f(50.f, 50.f) + startPosition);
    m_shape.setPoint(4, sf::Vector2f(40.f, 80.f) + startPosition);
    m_shape.setPoint(5, sf::Vector2f(30.f, 50.f) + startPosition);
    m_shape.setPoint(6, sf::Vector2f(0.f, 40.f) + startPosition);
    m_shape.setPoint(7, sf::Vector2f(30.f, 30.f) + startPosition);
    m_shape.setFillColor(sf::Color::Blue);
}

FinishStar::FinishStar(sf::Vector2f startPosition){
    this->initShape(startPosition);
}

FinishStar::~FinishStar(){

}

sf::FloatRect FinishStar::getBounds(){
    return m_shape.getGlobalBounds();
}

void FinishStar::update(){

}

void FinishStar::render(sf::RenderTarget& target){
    target.draw(m_shape);
}