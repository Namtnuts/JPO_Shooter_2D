#include "Classes/Enemy.h"

// Constructor and Destructor
Enemy::Enemy(){

}

Enemy::~Enemy(){

}

// Access functions
///////////////////////////////////////////////////////////
// This functions access private variebles of class
///////////////////////////////////////////////////////////
sf::FloatRect Enemy::getBounds(){
    return m_shape.getGlobalBounds();
}

std::vector<std::shared_ptr<Ray>> Enemy::getRays(){
    return m_rays;
}

bool Enemy::getIsPlayerDetected(){
    return m_playerDetected;
}

// Helper functions
sf::Vector2f Enemy::proj(sf::Vector2f A, sf::Vector2f B){
    ///////////////////////////////////////////////////////////
    // This function calculates projection of a vector to another vector
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //		A - vector is to be projected
    //		B - vector on which first vector is to be projected
    // OUTPUT:
    //		projection of vector
    // REMARKS:
    //      inspiraction from stackoverflow.com

    float dotAB = A.x * B.x + A.y * B.y;
    float dotBB = B.x * B.x + B.y * B.y;
    float k = dotAB / dotAB;
    return sf::Vector2f(k * B.x, k * B.y);
}

float Enemy::hypot2(sf::Vector2f A, sf::Vector2f B){
    ///////////////////////////////////////////////////////////
    // This function calculates dot product of vector
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //		A - first point of vector
    //		B - second point of vector
    // OUTPUT:
    //		dot product of vector
    // REMARKS:
    //      inspiraction from stackoverflow.com

    sf::Vector2f subAB(B.x - A.x, B.y - A.y);
    return subAB.x * subAB.x + subAB.y * subAB.y;
}


// Functions
bool Enemy::isPlayerDetected(sf::Vector2f playerPosition, sf::Vector2f rayStart, sf::Vector2f rayEnd, float playerRadius){
    ///////////////////////////////////////////////////////////
    // This function checks if player is deteced
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //		playerPosition - point (x,y) position of player
    //		rayStart - point (x,y) of start of ray
    //      rayEnd - point (x,y) of end of ray
    //      playerRadius - length of player's radius
    // OUTPUT:
    //		boolean
    // REMARKS:
    //      inspiraction from stackoverflow.com
    //      does not always work

    // Distance between player and start of ray
    sf::Vector2f distanceStartPlayer(playerPosition.x - rayStart.x , playerPosition.y - rayStart.y);

    // Length of ray
    sf::Vector2f distanceStartEnd(rayEnd.x - rayStart.x, rayEnd.y - rayStart.y);

    // Projection of vector between player and startRay to length of ray
    sf::Vector2f projectionVector = this->proj(distanceStartPlayer, distanceStartEnd);

    // Point thats start point to perpendicular vector to ray
    sf::Vector2f perpendicularPointToRay(projectionVector.x + rayStart.x, projectionVector.y + rayStart.y);

    // Perpendicular vector from player to ray
    sf::Vector2f distanceStartPerpendicularPoint(perpendicularPointToRay.x - rayStart.x, perpendicularPointToRay.y - rayStart.y);

    // Calculate k parameter which indicates if intersection exists 
    float k = std::abs(distanceStartEnd.x) > std::abs(distanceStartEnd.y) ? 
                        distanceStartPerpendicularPoint.x / distanceStartEnd.x 
                            : distanceStartPerpendicularPoint.y / distanceStartEnd.y;

    // Check diffrent scenarios and act accordingly
    float parameter{0.f};
    if(k <= 0.f){
        parameter = std::sqrt(this->hypot2(playerPosition, rayStart));
        if(parameter <= playerRadius) return true;
    }
    else if(k >= 1.f){
        parameter = std::sqrt(this->hypot2(playerPosition, rayEnd));
        if(parameter <= playerRadius) return true;
    }
    else{
        parameter = std::sqrt(this->hypot2(playerPosition, perpendicularPointToRay));
        if(parameter <= playerRadius) return true;
    }
    return false;
}

bool Enemy::isDead(){
    ///////////////////////////////////////////////////////////
    // This function checks if enemy is dead
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //
    // OUTPUT:
    //		boolean
    // REMARKS:

    if(m_healthPoints <= 0) return true;
    else return false;
}

void Enemy::gotShot(){
    ///////////////////////////////////////////////////////////
    // This function checks if enemy got shot
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //
    // OUTPUT:
    //		takes one health point
    // REMARKS:

    --m_healthPoints;
}

void Enemy::move(){
    ///////////////////////////////////////////////////////////
    // This function moves shape and calls rotate of rays
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //
    // OUTPUT:
    //		shape is moved
    // REMARKS:

    // Get index from path to move to
    int index = m_path->getMovingTo();

    // Get vertex from path to move by giving index
    sf::Vector2f vertex = m_path->getVertexPosition(index);

    // Get angle from path to rotate rays by gicing index
    float angle = m_path->getAngle(index);

    // Get direction of rotation from path by giving index (its left of right)
    std::string rotationDirection = m_path->getRotationDirection(index);

    // Get position of shape and make it center of shape
    sf::Vector2f pos = m_shape.getPosition() + sf::Vector2f(10.f,10.f);
   
    // Check if angle is positive or negative and act accordingly
    // Purpose of this operation: we need to round our angle to check
    //      because we are doing some simplifications to round to second decimal place
    //      and we always want to go up (meaning bigger number regardless of sign) so if
    //      angle is positive we need to ceil but if its negative we need to floor
    float angleCheck = angle;
    if(angle >= 0.f){
        angleCheck = std::floor(angleCheck * 100.f) / 100.f;
    }
    else{
        angleCheck = std::ceil(angleCheck * 100.f) / 100.f;
    }
    
    // Get direction to check 
    // ArcTan of current direction ceil to second decimal place
    float directionCheck = std::ceil(atan2(m_direction.y, m_direction.x)*100.f) / 100.f;

    // Check if position of shape is the same as vectex we are moving to and also
    // check if current angle (directionCheck) isn't equal to angle to check
    // if so only rotate rays, do not move
    if(vertex == pos && angleCheck != directionCheck){
            this->rotate(rotationDirection);
    }

    // this is needed because of this condition vertex==pos
    // even when we are done rotating we still need to move
    // so we just move once and condition above will be false in next call
    else if(vertex == pos && angleCheck == directionCheck){
        m_direction = sf::Vector2f(round(m_direction.x), round(m_direction.y));
        m_shape.move(sf::Vector2f(m_direction.x * m_movementSpeed, m_direction.y * m_movementSpeed));
        m_path->changeNextVertex();
    }

    // Move shape by given vector
    else{
        m_shape.move(sf::Vector2f(m_direction.x * m_movementSpeed, m_direction.y * m_movementSpeed));
    }
}

void Enemy::rotate(std::string rotationDirection){
    ///////////////////////////////////////////////////////////
    // This function rotates rays
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //		rotationDirection - direction of rotation (left or right)
    // OUTPUT:
    //		rays are rotated
    // REMARKS:

    // Checks if direction of rotation is left or right
    float rotationAngle = rotationDirection == static_cast<std::string>("left") ? -0.01f : 0.01f;

    // Loop through all rays and rotate them by giving angle
    for(auto &ray : m_rays){
        ray->rotate(rotationAngle);
    }

    // Update direction of enemy
    float newX = m_direction.x * cos(rotationAngle) - m_direction.y * sin(rotationAngle);
    float newY = m_direction.x * sin(rotationAngle) + m_direction.y * cos(rotationAngle); 
    m_direction = sf::Vector2f(newX, newY);
}

void Enemy::updateRays(sf::VertexArray& walls, sf::Vector2f playerPosition, float playerRadius){
    ///////////////////////////////////////////////////////////
    // This function updates rays
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //		
    //      walls - all lines (two vertcies) representing map (walls)
    //		playerPosition - point (x,y) position of player
    //      playerRadius - length of player's radius
    // OUTPUT:
    //		updates rays
    // REMARKS:

    // Get position of enemy and make it center of shape by adding radius of enemy
    sf::Vector2f enemyPosition(m_shape.getPosition() + sf::Vector2f(m_shape.getRadius(), m_shape.getRadius()));

    // Loop through all rays update them and call isPlayerDeteced() and if player is detected change value of  right variable
    for(auto &ray : m_rays){
        ray->update(walls, enemyPosition, 0.f);
        if(this->isPlayerDetected(playerPosition,ray->getStartPoint(), ray->getEndPoint(), playerRadius)){
            m_playerDetected = true;
        }
    }
}

void Enemy::update(sf::VertexArray& walls, sf::Vector2f playerPosition, float playerRadius){
    ///////////////////////////////////////////////////////////
    // This function updates enemy (calls functions updateRays and move)
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      walls - all lines (two vertcies) representing map (walls)
    //		playerPosition - point (x,y) position of player
    //      playerRadius - length of player's radius
    // OUTPUT:
    //		enemy is updated
    // REMARKS:

    this->updateRays(walls, playerPosition, playerRadius);
    this->move();
}

void Enemy::renderRays(sf::RenderTarget& target){
    ///////////////////////////////////////////////////////////
    // This function render rays
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      target - object to render to
    // OUTPUT:
    //		rays are rendered
    // REMARKS:

    //Loop through all rays and call their render function passing target
    for (auto &ray : m_rays){
        ray->render(target);
    } 
}

void Enemy::render(sf::RenderTarget& target){
    ///////////////////////////////////////////////////////////
    // This function renders shape (calls renderRays)
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      target - object to render to
    // OUTPUT:
    //		enemy is rendered
    // REMARKS:

    // Call render rays
    this->renderRays(target);

    // Render shape
    target.draw(m_shape);
}