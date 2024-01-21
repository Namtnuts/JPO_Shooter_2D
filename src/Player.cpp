#include "Classes/Player.h"

// Private functions
void Player::initVariables(){
    ///////////////////////////////////////////////////////////
    // This function initialize vairbales
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		variables are initialized
    // REMARKS:

    m_movementSpeed = 2.f;
    m_fov = 360.f;
    m_playerDirection = sf::Vector2f(0.f, -1.f);
    m_offset = acos((m_playerDirection.x * 1.f) / (sqrt(pow(m_playerDirection.x, 2) + pow(m_playerDirection.y, 2))));
    m_shootCooldownMax = 10.f;
    m_shootCooldown = m_shootCooldownMax;
}

void Player::initShape(){
    ///////////////////////////////////////////////////////////
    // This function initialize shape 
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //
    // REMARKS:

    m_shape.setFillColor(sf::Color::Green);
    m_shape.setRadius(10.f);
    m_shape.setPosition(50.f, 50.f);
}

void Player::initRays(){
    ///////////////////////////////////////////////////////////
    // This function initialize rays
    ///////////////////////////////////////////////////////////

    // Check if direction is lower than 0.f and multiply current offset by right value
    m_offset = (m_playerDirection.y < 0.f) ? m_offset * -1.f : m_offset * 1.f;
    float fov = m_fov * (M_PI / 180.f);

    // Intialize rays regadring offset and fov
    for(float angle = m_offset - fov / 2; angle < m_offset + fov / 2; angle += 0.01f){
        m_rays.push_back(std::make_shared<Ray>(m_shape.getPosition(), sf::Vector2f(cos(angle), sin(angle)), sf::Color(255,255,255,0), 2000.f));
    }
}

void Player::initCrosshair(){
    ///////////////////////////////////////////////////////////
    // This function initialize crosshair 
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //
    // REMARKS:

    m_crosshair = std::make_unique<Ray>(m_shape.getPosition(), sf::Vector2f(cos(m_offset), sin(m_offset)), sf::Color::White, 2000.f);
}

// Constructor and destructor
Player::Player(){
    this->initVariables();
    this->initShape();
    this->initRays();
    this->initCrosshair();
}

Player::~Player(){

}

// Modifires
///////////////////////////////////////////////////////////
// These functions modify private variebles of class
///////////////////////////////////////////////////////////
void Player::setPosition(sf::Vector2f position){
    m_shape.setPosition(position);
}

// Accessors
///////////////////////////////////////////////////////////
// These functions access private variebles of class
///////////////////////////////////////////////////////////
sf::Vector2f Player::getPosition(){
    return m_shape.getPosition();
}

float Player::getRadius(){
    return m_shape.getRadius();
}

sf::Vector2f Player::getDirection(){
    return m_playerDirection;
}

sf::FloatRect Player::getGlobalBounds(){
    return m_shape.getGlobalBounds();
}

std::vector<std::shared_ptr<Ray>> Player::getRays(){
    return m_rays;
}

bool Player::checkPlayerMapIntersect(sf::Vector2f moveDirection){
    ///////////////////////////////////////////////////////////
    // This function checks in player is intersecting with map
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      movedirection - direction of movement
    // OUTPUT:
    //		boolean
    // REMARKS:
    //      this function was buggy so here is basic explanation
    //      function takes move direction as parameter e.g (1.f, 0.f) which means player is moving in right direction
    //      it iterates through all rays and checks if length of current ray is lower than 10.f (radius of player)
    //      then it gets ray direction from current ray and checks which axis ray is closer to (X or Y)
    //      and then it replace ray direction for exact direction -> this operation is needed because when function had been tested 
    //      ray direction were for e.g (-0.8823, 0.5322) which had to be converted to (-1.f, 0.f) to check with move direction
    //      this operation goes like this: check if abs(x) > abs(y) if so ray direction: x value(if >0 then ceil else floor) , y value(0.f)
    //      and if not ray direction: x value(0.f) , y value(if >0 then ceil else floor)
    //      this operation function is checking if this exact ray directions match move direction if so that means player is intersecting with map
    //      and function returns true
    //      if none of above if statements were true loop ends which means player isn't intersecting with map so function returns false

    for(auto &ray : m_rays){
        //check if ray length is lower than 10.f
        if(ray->getRayLength() < 10.f){
            sf::Vector2f rayDiraction = ray->getDirection();
            
            //check which axis is "more important"
            if(std::abs(rayDiraction.x) > std::abs(rayDiraction.y)){
                //if X axis then replace ray direction for exact direction
                rayDiraction = sf::Vector2f(rayDiraction.x > 0.f ? std::ceil(rayDiraction.x) : std::floor(rayDiraction.x) , 0.f);
                
                //check if exact direction matches move direction if so returns true
                if(rayDiraction.x == moveDirection.x && rayDiraction.y == moveDirection.y) return true;
            }
            else{
                //if Y axis then replace ray direction for exact direction
                rayDiraction = sf::Vector2f(0.f, rayDiraction.y > 0.f ? std::ceil(rayDiraction.y) : std::floor(rayDiraction.y));

                //check if exact direction matches move direction if so returns true
                if(rayDiraction.x == moveDirection.x && rayDiraction.y == moveDirection.y) return true;
            }
        }
    }
    //loop ended without finding intersection then return false
    return false;
}

const bool Player::canshoot(){
    ///////////////////////////////////////////////////////////
    // This function checks if player can shoot
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		boolean
    // REMARKS:

    if(m_shootCooldown >= m_shootCooldownMax){
        m_shootCooldown = 0.f;
        return true;
    }
    return false;
}

void Player::updateInput(){
    ///////////////////////////////////////////////////////////
    // This function updates input if WSAD keys are pressed and checks if player is intersecting with map
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		input is handled (WSAD)
    // REMARKS:

    //up
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
        if(!(this->checkPlayerMapIntersect(sf::Vector2f(0.f, -1.f)))) this->m_shape.move(0.f, -m_movementSpeed);
    }
    //down
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
        if(!(this->checkPlayerMapIntersect(sf::Vector2f(0.f, 1.f)))) this->m_shape.move(0.f, m_movementSpeed);
    }
    //left
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        if(!(this->checkPlayerMapIntersect(sf::Vector2f(-1.f, 0.f)))) this->m_shape.move(-m_movementSpeed, 0.f);
    }
    //right
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        if(!(this->checkPlayerMapIntersect(sf::Vector2f(1.f, 0.f)))) this->m_shape.move(m_movementSpeed, 0.f);
    }
}

void Player::updateRays(sf::VertexArray& walls, sf::Vector2i mousePosition){
    ///////////////////////////////////////////////////////////
    // This function updates rays
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      walls - lines (two vertices) representing walls
    //      mousePosition - mouse position (x,y)
    // OUTPUT:
    //		rays are updated
    // REMARKS:

    //get player's position and adjust it that is middle of circle not top left corner of the circle
    sf::Vector2f playerPosition = m_shape.getPosition() + sf::Vector2f(m_shape.getRadius(), m_shape.getRadius());

    //calculate diffrence between mousePosition and player's position
    sf::Vector2f diff = sf::Vector2f(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) - playerPosition;

    //calculate angle between mouse and player's direction relative to player's position
    float angle = atan2(diff.y, diff.x);
    
    //calculate current angle of player relative to (1,0) vector
    float currAngle = atan2(m_playerDirection.y, m_playerDirection.x);
  
    //set new direction   
    m_playerDirection = sf::Vector2f(cos(angle), sin(angle));       

    //iterate through all the rays
    for(auto &ray : m_rays){
        //update ray passing walls playerPosition and diffrence between angle of the mouse relative to (1,0) and current angle of the player relative to (1,0)
        ray->update(walls, playerPosition, angle - currAngle);
    }

    //update ray responsible for representing crosshair
    m_crosshair->update(walls, playerPosition, angle - currAngle);
}

void Player::updateShoot(){
    ///////////////////////////////////////////////////////////
    // This function updates cooldown for shooting
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		cooldown of shooting is updated
    // REMARKS:

    if(m_shootCooldown < m_shootCooldownMax)
        m_shootCooldown += 0.5f;
}

void Player::update(sf::VertexArray& walls, sf::Vector2i mousePosition){
    ///////////////////////////////////////////////////////////
    // This function updates player
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		player is updated
    // REMARKS:

    this->updateInput();
    this->updateRays(walls, mousePosition);
    this->updateShoot();
    
}

void Player::renderRays(sf::RenderTarget& target){
    ///////////////////////////////////////////////////////////
    // This function renders rays
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      target - object to render to
    // OUTPUT:
    //		rays are rendered)
    // REMARKS:

    //render all rays
    for (auto &ray : m_rays){
        ray->render(target);
    }

    //render crosshair
    m_crosshair->render(target);
}

void Player::render(sf::RenderTarget& target){
    ///////////////////////////////////////////////////////////
    // This function renders shape and calls renderRays
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      target - object to render to
    // OUTPUT:
    //		shape is rendered
    // REMARKS:

    this->renderRays(target);
    target.draw(m_shape);
}