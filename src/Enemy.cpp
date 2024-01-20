#include "Classes/Enemy.h"

Enemy::Enemy(){

}

Enemy::~Enemy(){

}

sf::FloatRect Enemy::getBounds(){
    return m_shape.getGlobalBounds();
}

std::vector<std::shared_ptr<Ray>> Enemy::getRays(){
    return m_rays;
}

bool Enemy::getIsPlayerDetected(){
    return m_playerDetected;
}

sf::Vector2f Enemy::proj(sf::Vector2f A, sf::Vector2f B){
    float dotAB = A.x * B.x + A.y * B.y;
    float dotBB = B.x * B.x + B.y * B.y;
    float k = dotAB / dotAB;
    return sf::Vector2f(k * B.x, k * B.y);
}

float Enemy::hypot2(sf::Vector2f A, sf::Vector2f B){
    sf::Vector2f subAB(B.x - A.x, B.y - A.y);
    return subAB.x * subAB.x + subAB.y * subAB.y;
}

bool Enemy::isPlayerDetected(sf::Vector2f playerPosition, sf::Vector2f rayStart, sf::Vector2f rayEnd, float playerRadius){
    sf::Vector2f distanceStartPlayer(playerPosition.x - rayStart.x , playerPosition.y - rayStart.y);
    sf::Vector2f distanceStartEnd(rayEnd.x - rayStart.x, rayEnd.y - rayStart.y);
    sf::Vector2f projectionVector = this->proj(distanceStartPlayer, distanceStartEnd);
    sf::Vector2f perpendicularPointToRay(projectionVector.x + rayStart.x, projectionVector.y + rayStart.y);
    sf::Vector2f distanceStartPerpendicularPoint(perpendicularPointToRay.x - rayStart.x, perpendicularPointToRay.y - rayStart.y);
    float k = std::abs(distanceStartEnd.x) > std::abs(distanceStartEnd.y) ? 
                        distanceStartPerpendicularPoint.x / distanceStartEnd.x 
                            : distanceStartPerpendicularPoint.y / distanceStartEnd.y;

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
    if(m_healthPoints <= 0) return true;
    else return false;
}

void Enemy::gotShot(){
    --m_healthPoints;
}

void Enemy::move(){
    int index = m_path->getMovingTo();
    sf::Vector2f vertex = m_path->getVertexPosition(index);
    float angle = m_path->getAngle(index);
    std::string rotationDirection = m_path->getRotationDirection(index);

    sf::Vector2f pos = m_shape.getPosition() + sf::Vector2f(10.f,10.f);
   
    float angleCheck = angle;
    if(angle >= 0.f){
        angleCheck = std::floor(angleCheck * 100.f) / 100.f;
    }
    else{
        angleCheck = std::ceil(angleCheck * 100.f) / 100.f;
    }
    
    float directionCheck = std::ceil(atan2(m_direction.y, m_direction.x)*100.f) / 100.f;

    if(vertex == pos && angleCheck != directionCheck){
            this->rotate(rotationDirection);
            
    }
    else if(vertex == pos && angleCheck == directionCheck){
        m_direction = sf::Vector2f(round(m_direction.x), round(m_direction.y));
        m_shape.move(sf::Vector2f(m_direction.x * m_movementSpeed, m_direction.y * m_movementSpeed));
        m_path->changeNextVertex();
    }
    else{
        m_shape.move(sf::Vector2f(m_direction.x * m_movementSpeed, m_direction.y * m_movementSpeed));
    }
}

void Enemy::rotate(std::string rotationDirection){
    float rotationAngle = rotationDirection == static_cast<std::string>("left") ? -0.01f : 0.01f;

    for(auto &ray : m_rays){
        ray->rotate(rotationAngle);
    }
    float newX = m_direction.x * cos(rotationAngle) - m_direction.y * sin(rotationAngle);
    float newY = m_direction.x * sin(rotationAngle) + m_direction.y * cos(rotationAngle); 
    m_direction = sf::Vector2f(newX, newY);
}

void Enemy::updateRays(sf::VertexArray& walls, sf::Vector2f playerPosition, float playerRadius){
    sf::Vector2f enemyPosition(m_shape.getPosition() + sf::Vector2f(m_shape.getRadius(), m_shape.getRadius()));
    for(auto &ray : m_rays){
        ray->update(walls, enemyPosition, 0.f);
        if(this->isPlayerDetected(playerPosition,ray->getStartPoint(), ray->getEndPoint(), playerRadius)){
            m_playerDetected = true;
        }
    }
}

void Enemy::update(sf::VertexArray& walls, sf::Vector2f playerPosition, float playerRadius){
    this->updateRays(walls, playerPosition, playerRadius);
    this->move();
}

void Enemy::renderRays(sf::RenderTarget& target){
    for (auto &ray : m_rays){
        ray->render(target);
    } 
}

void Enemy::render(sf::RenderTarget& target){
    this->renderRays(target);
    target.draw(m_shape);
}