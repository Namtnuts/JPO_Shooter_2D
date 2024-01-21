#include "Classes/Ray.h"

//Private functions
void Ray::initVariables(sf::Vector2f startPoint, sf::Vector2f direction, sf::Color color, float length){
    ///////////////////////////////////////////////////////////
    // This function initialize variables
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      startPoint - starting point (x, y)
    //      direction - direction of ray (x,y)
    //      color - color of line (ray)
    //      length - length of line (ray)
    // OUTPUT:
    //      variables are initialized
    // REMARKS:

    m_startPoint = startPoint;
    m_direction = direction;
    m_defaultRayLength = length;
    m_rayLength = m_defaultRayLength;
    m_endPoint = startPoint + m_direction*m_rayLength;
    m_ray[0].position = m_startPoint;
    m_ray[1].position = m_endPoint;
    m_ray[0].color = color;
    m_ray[1].color = color;
}

//Constructor and destructor
Ray::Ray(sf::Vector2f startPoint, sf::Vector2f direction, sf::Color color, float length){
    this->initVariables(startPoint, direction, color, length);
}

Ray::~Ray(){

}

// Modifires
///////////////////////////////////////////////////////////
// These functions modify private variebles of class
///////////////////////////////////////////////////////////
void Ray::setRayLength(float length){
    m_rayLength = length;
}

// Accessors
///////////////////////////////////////////////////////////
// These functions access private variebles of class
///////////////////////////////////////////////////////////
sf::Vertex Ray::getRay(){
    return m_ray[2];
}

float Ray::getRayLength(){
    return m_rayLength;
}

sf::Vector2f Ray::getStartPoint(){
    return m_startPoint;
}

sf::Vector2f Ray::getEndPoint(){
    return m_endPoint;
}

sf::Vector2f Ray::getDirection(){
    return m_direction;
}



void Ray::rotate(float angle){
    ///////////////////////////////////////////////////////////
    // This function rotates ray by given angle
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      angle - angle by which ray is to be rotated
    // OUTPUT:
    //	    ray is rotated
    // REMARKS:

    float newX = m_direction.x * cos(angle) - m_direction.y * sin(angle);
    float newY = m_direction.x * sin(angle) + m_direction.y * cos(angle); 
    m_direction = sf::Vector2f(newX, newY);
}

void Ray::collisionWalls(sf::VertexArray& walls){
    ///////////////////////////////////////////////////////////
    // This function checks if ray is intersecting with walls
    // and updates its length if so
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      walls - lines (two vertices) representing walls
    // OUTPUT:
    //	    ray length is/is not updated
    // REMARKS:
    //      source: wikipedia

    int numberOfWalls = walls.getVertexCount();
    for (size_t i = 0; i < numberOfWalls; i++){
        if(i%2==0) continue;
        else{
            //start and end points of the wall
            const float x1 = walls[i-1].position.x;
            const float y1 = walls[i-1].position.y;
            const float x2 = walls[i].position.x;
            const float y2 = walls[i].position.y;

            //start and end points of the ray
            const float x3 = m_startPoint.x;
            const float y3 = m_startPoint.y;
            const float x4 = m_endPoint.x;
            const float y4 = m_endPoint.y;

            //calculate denominator and check if equals 0, if so then continue(ray and wall are parallel)
            const float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
            if(den==0) continue;

            //calculate variables t and u 
            const float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
            const float u = ((x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2)) / den;

            //calculate lenght of the ray to check which ray is the closest to wall
            float closest = std::numeric_limits<float>::infinity();
            float distance = std::sqrt(std::pow(x1 + t * (x2 - x1) - x3, 2) + std::pow(y1 + t * (y2 - y1) + y3, 2));

            //check if 0<t<1 and 0<u<1 which indicates intersection
            if((t > 0 && t < 1) && (u > 0 && u < 1)){
                        
                //check if ray intersecting is the closest
                if(distance < closest){
                    //substitute previous value of end ray to calculated intersect points
                    m_endPoint = sf::Vector2f(x1 + t * (x2 - x1), y1 + t * (y2 - y1));
                }
            }
        }
    }
}

void Ray::update(sf::VertexArray& walls, sf::Vector2f playerPosition, float angle){
    ///////////////////////////////////////////////////////////
    // This function updates rays
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      walls - lines (two vertices) representing walls
    //      playerposition - point (x,y) where player's shape is
    //      angle - angle by which ray is to be rotated
    // OUTPUT:
    //	    updates position and length of ray(if needed)
    // REMARKS:

    //set begin of the ray (m_startPoint) to player's position
    m_startPoint = playerPosition;

    //set end of the ray (m_endPoint) 
    m_endPoint = playerPosition + m_direction * m_defaultRayLength;

    //rotate ray based on given angle
    this->rotate(angle);

    //check collision with walls on the map and adjust ray
    this->collisionWalls(walls);

    //calculate current ray length
    m_rayLength = sqrt(pow(m_startPoint.x - m_endPoint.x, 2) + pow(m_startPoint.y - m_endPoint.y, 2));

    //set values of Line
    m_ray[0].position = m_startPoint;
    m_ray[1].position = m_endPoint;
}

void Ray::render(sf::RenderTarget& target){
    ///////////////////////////////////////////////////////////
    // This function renders ray
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      target - object to render to
    // OUTPUT:
    //	    ray is rendered
    // REMARKS:
    
    target.draw(m_ray, 2, sf::Lines);
}