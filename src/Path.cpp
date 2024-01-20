#include "Classes/Path.h"

void Path::initVariables(int type){
    m_type = type;
}

void Path::initPath(){
    switch (m_type)
    {
    case GUARD_1:
        m_path.push_back(std::make_tuple(sf::Vector2f(130.f, 200.f), -M_PI / 2.f, "left")); //0
        m_path.push_back(std::make_tuple(sf::Vector2f(130.f, 150.f), -M_PI, "left"));   //1
        m_path.push_back(std::make_tuple(sf::Vector2f(50.f, 150.f), M_PI / 2.f, "left"));   //2
        m_path.push_back(std::make_tuple(sf::Vector2f(50.f, 200.f), 0.f, "left"));      //3

        m_movingOrder.push_back(0);
        m_movingOrder.push_back(1);
        m_movingOrder.push_back(2);
        m_movingOrder.push_back(3);

        m_movingTo = m_movingOrder[0];
        m_startPosition = sf::Vector2f(90.f, 200.f);
        m_currentDirection = sf::Vector2f(cos(0.f), sin(0.f));

        break;
    case GUARD_2:
        m_path.push_back(std::make_tuple(sf::Vector2f(230.f, 187.5f), 0.f, "right"));    //0
        m_path.push_back(std::make_tuple(sf::Vector2f(400.f, 187.5f), M_PI, "left"));  //1

        m_movingOrder.push_back(0);
        m_movingOrder.push_back(1);

        m_startPosition = sf::Vector2f(315.f, 187.5f);
        m_currentDirection = sf::Vector2f(cos(M_PI), sin(M_PI));
        m_movingTo = m_movingOrder[0];

        break;
    case GUARD_3:
        m_path.push_back(std::make_tuple(sf::Vector2f(230.f, 62.5f), 0.f, "left"));     //0
        m_path.push_back(std::make_tuple(sf::Vector2f(400.f, 62.5f), M_PI, "right"));   //1
    
        m_movingOrder.push_back(1);
        m_movingOrder.push_back(0);

        m_startPosition = sf::Vector2f(315.f, 62.5f);
        m_currentDirection = sf::Vector2f(cos(0.f), sin(0.f));
        m_movingTo = m_movingOrder[0];

        break;
    case COUNTERTERRORIST_1:
        m_path.push_back(std::make_tuple(sf::Vector2f(492.f, 50.f), M_PI / 4.f, "left"));   //0
        m_path.push_back(std::make_tuple(sf::Vector2f(630.f, 188.f), -M_PI / 4.f, "left")); //1
        m_path.push_back(std::make_tuple(sf::Vector2f(768.f, 50.f), M_PI * 3.f / 4.f, "right")); //2
        m_path.push_back(std::make_tuple(sf::Vector2f(630.f, 188.f), -M_PI * 3.f / 4.f, "right")); //3
        
        m_movingOrder.push_back(1);
        m_movingOrder.push_back(2);
        m_movingOrder.push_back(3);
        m_movingOrder.push_back(0);

        m_startPosition = sf::Vector2f(630.f, 188.f);
        m_currentDirection = sf::Vector2f(cos(-M_PI/4.f), sin(-M_PI/4.f));
        m_movingTo = m_movingOrder[0];

        break;
    case COUNTERTERRORIST_2:
        m_path.push_back(std::make_tuple(sf::Vector2f(768.f, 325.f), -M_PI * 3.f / 4.f, "left"));   //0
        m_path.push_back(std::make_tuple(sf::Vector2f(680.f, 237.f), M_PI / 2.f, "left")); //1
        m_path.push_back(std::make_tuple(sf::Vector2f(680.f, 325.f), M_PI, "right")); //2
        m_path.push_back(std::make_tuple(sf::Vector2f(500.f, 325.f), 0.f, "right")); //3
        
        m_movingOrder.push_back(0);
        m_movingOrder.push_back(1);
        m_movingOrder.push_back(2);
        m_movingOrder.push_back(3);

        m_startPosition = sf::Vector2f(700.f, 325.f);
        m_currentDirection = sf::Vector2f(cos(0.f), sin(0.f));
        m_movingTo = m_movingOrder[0];

        break;
    case COUNTERTERRORIST_3:
        m_path.push_back(std::make_tuple(sf::Vector2f(690.f, 370.f), M_PI / 2.f, "left"));   //0
        m_path.push_back(std::make_tuple(sf::Vector2f(690.f, 555.f), 0.f, "left")); //1
        m_path.push_back(std::make_tuple(sf::Vector2f(755.f, 555.f), -M_PI / 2.f, "left")); //2
        m_path.push_back(std::make_tuple(sf::Vector2f(755.f, 430.f), M_PI / 2.f, "left")); //3
        m_path.push_back(std::make_tuple(sf::Vector2f(755.f, 555.f), M_PI, "right")); //4
        m_path.push_back(std::make_tuple(sf::Vector2f(690.f, 555.f), -M_PI / 2.f, "right")); //5

        m_movingOrder.push_back(0);
        m_movingOrder.push_back(1);
        m_movingOrder.push_back(2);
        m_movingOrder.push_back(3);
        m_movingOrder.push_back(4);
        m_movingOrder.push_back(5);

        m_startPosition = sf::Vector2f(690.f, 430.f);
        m_currentDirection = sf::Vector2f(cos(-M_PI / 2.f), sin(-M_PI / 2.f));
        m_movingTo = m_movingOrder[0];

        break;
    case COUNTERTERRORIST_4:
        m_path.push_back(std::make_tuple(sf::Vector2f(625.f, 395.f), M_PI, "left"));   //0
        m_path.push_back(std::make_tuple(sf::Vector2f(625.f, 555.f), -M_PI / 2.f, "left")); //1
        m_path.push_back(std::make_tuple(sf::Vector2f(395.f, 555.f), 0.f, "left")); //2
        m_path.push_back(std::make_tuple(sf::Vector2f(395.f, 395.f), M_PI / 2.f, "left")); //3

        m_movingOrder.push_back(3);
        m_movingOrder.push_back(2);
        m_movingOrder.push_back(1);
        m_movingOrder.push_back(0);

        m_startPosition = sf::Vector2f(515.f, 395.f);
        m_currentDirection = sf::Vector2f(cos(M_PI), sin(M_PI));
        m_movingTo = m_movingOrder[0];

        break;
    case SPECIALFORCE:
        m_path.push_back(std::make_tuple(sf::Vector2f(75.f, 286.f), M_PI / 2.f, "left"));   //0
        m_path.push_back(std::make_tuple(sf::Vector2f(276.f, 286.f), M_PI, "left")); //1
        m_path.push_back(std::make_tuple(sf::Vector2f(276.f, 565.f), -M_PI / 2.f, "left")); //2
        m_path.push_back(std::make_tuple(sf::Vector2f(75.f, 565.f), 0.f, "left")); //3

        m_movingOrder.push_back(3);
        m_movingOrder.push_back(2);
        m_movingOrder.push_back(1);
        m_movingOrder.push_back(0);

        m_startPosition = sf::Vector2f(75.f, 445.f);
        m_currentDirection = sf::Vector2f(cos(M_PI / 2.f), sin(M_PI / 2.f));
        m_movingTo = m_movingOrder[0];

        break;
    default:
        break;
    }
}

Path::Path(int type){
    this->initVariables(type);
    this->initPath();
}

Path::~Path(){

}

sf::Vector2f Path::getStartPosition(){
    return m_startPosition;
}

sf::Vector2f Path::getCurrentDirection(){
    return m_currentDirection;
}

sf::Vector2f Path::getVertexPosition(int index){
    return std::get<0>(m_path[index]);
}

float Path::getAngle(int index){
    return std::get<1>(m_path[index]);
}

std::string Path::getRotationDirection(int index){
    return std::get<2>(m_path[index]);
}

int Path::getMovingTo(){
    return m_movingTo;
}

void Path::changeNextVertex(){
    auto it = std::find(m_movingOrder.begin(), m_movingOrder.end(), m_movingTo); 
  
    if (it != m_movingOrder.end()){ 
        int index = it - m_movingOrder.begin();
        if(index + 1 < m_movingOrder.size()){
            m_movingTo = m_movingOrder[index + 1];
        }
        else{
            m_movingTo = m_movingOrder[0];
        }
    }
}