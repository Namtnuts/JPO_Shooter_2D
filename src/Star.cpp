#include "Classes/Star.h"

// Private functions
void Star::initShape(sf::Vector2f startPosition){
    ///////////////////////////////////////////////////////////
    // This function initialize shape
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      startPosition - starting position of shape (x,y)
    // OUTPUT:
    //	    shape is initialized
    // REMARKS:

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

// Constructor and Destructor
Star::Star(sf::Vector2f startPosition){
    this->initShape(startPosition);
}

Star::~Star(){

}

// Accessors
///////////////////////////////////////////////////////////
// These functions access private variebles of class
///////////////////////////////////////////////////////////
sf::FloatRect Star::getBounds(){
    return m_shape.getGlobalBounds();
}

void Star::update(){
    ///////////////////////////////////////////////////////////
    // This function currently does nothing (this function is for future)
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    // REMARKS:
    //      maybe add more features to game
}

void Star::render(sf::RenderTarget& target){
    ///////////////////////////////////////////////////////////
    // This function renders shape
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      target - object to render to
    // OUTPUT:
    //		shape is rendered
    // REMARKS:

    target.draw(m_shape);
}