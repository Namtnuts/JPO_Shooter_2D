#include "Classes/Map.h"

// Constructor and Destructor
Map::Map(){
    ///////////////////////////////////////////////////////////
    // This is contructor of this class
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //	    sets all vertices of map
    // REMARKS:
    //      for future this might be better if use reading from file
    //      TODO!!!

    m_walls.setPrimitiveType(sf::Lines);
    m_walls.resize(74);
    m_walls[0].position = sf::Vector2f(1.f, 1.f);
    m_walls[1].position = sf::Vector2f(800.f, 1.f);

    m_walls[2].position = sf::Vector2f(800.f, 1.f);
    m_walls[3].position = sf::Vector2f(800.f, 590.f);
    
    m_walls[4].position = sf::Vector2f(800.f, 599.f);
    m_walls[5].position = sf::Vector2f(1.f, 599.f);

    m_walls[6].position = sf::Vector2f(1.f, 599.f);
    m_walls[7].position = sf::Vector2f(1.f, 1.f);

    //kwadrat środek
    m_walls[8].position = sf::Vector2f(0.f, 250.f);
    m_walls[9].position = sf::Vector2f(540.f, 250.f);

    m_walls[10].position = sf::Vector2f(450.f, 70.f);
    m_walls[11].position = sf::Vector2f(450.f, 350.f);

    m_walls[12].position = sf::Vector2f(670.f, 350.f);
    m_walls[13].position = sf::Vector2f(350.f, 350.f); 

    m_walls[14].position = sf::Vector2f(350.f, 370.f);
    m_walls[15].position = sf::Vector2f(350.f, 320.f); 

    //dodatki
    m_walls[16].position = sf::Vector2f(350.f, 280.f);
    m_walls[17].position = sf::Vector2f(350.f, 250.f);

    m_walls[18].position = sf::Vector2f(450.f, 1.f);
    m_walls[19].position = sf::Vector2f(450.f, 30.f);

    m_walls[20].position = sf::Vector2f(800.f, 350.f);
    m_walls[21].position = sf::Vector2f(710.f, 350.f);

    m_walls[22].position = sf::Vector2f(350.f, 410.f);
    m_walls[23].position = sf::Vector2f(350.f, 600.f);

    m_walls[24].position = sf::Vector2f(710.f, 350.f);
    m_walls[25].position = sf::Vector2f(710.f, 510.f);

    m_walls[26].position = sf::Vector2f(670.f, 350.f);
    m_walls[27].position = sf::Vector2f(670.f, 510.f);

    //prostokąt strefa 3
    m_walls[28].position = sf::Vector2f(440.f, 440.f);
    m_walls[29].position = sf::Vector2f(440.f, 510.f);

    m_walls[30].position = sf::Vector2f(440.f, 510.f);
    m_walls[31].position = sf::Vector2f(580.f, 510.f);

    m_walls[32].position = sf::Vector2f(580.f, 510.f);
    m_walls[33].position = sf::Vector2f(580.f, 440.f);

    m_walls[34].position = sf::Vector2f(580.f, 440.f);
    m_walls[35].position = sf::Vector2f(440.f, 440.f);

    //trójkąty
    m_walls[36].position = sf::Vector2f(450.f, 70.f);
    m_walls[37].position = sf::Vector2f(630.f, 250.f);

    m_walls[38].position = sf::Vector2f(505.f, 0.f);
    m_walls[39].position = sf::Vector2f(630.f, 125.f);

    m_walls[40].position = sf::Vector2f(630.f, 125.f);
    m_walls[41].position = sf::Vector2f(755.f, 0.f);

    m_walls[42].position = sf::Vector2f(692.5f, 187.5f);
    m_walls[43].position = sf::Vector2f(800.f, 80.f);

    m_walls[44].position = sf::Vector2f(692.5f, 187.5f);
    m_walls[45].position = sf::Vector2f(800.f, 295.f);

    //prostokąt strefa 2
    m_walls[46].position = sf::Vector2f(630.f, 250.f);
    m_walls[47].position = sf::Vector2f(630.f, 300.f);

    m_walls[48].position = sf::Vector2f(630.f, 300.f);
    m_walls[49].position = sf::Vector2f(540.f, 300.f);

    m_walls[50].position = sf::Vector2f(540.f, 300.f);
    m_walls[51].position = sf::Vector2f(540.f, 250.f);

    //strefa 1
    m_walls[52].position = sf::Vector2f(180.f, 0.f);
    m_walls[53].position = sf::Vector2f(180.f, 210.f);

    m_walls[54].position = sf::Vector2f(180.f, 125.f);
    m_walls[55].position = sf::Vector2f(360.f, 125.f);

    m_walls[56].position = sf::Vector2f(0.f, 100.f);
    m_walls[57].position = sf::Vector2f(140.f, 100.f);

    //kwadraty strefa 4
    //1
    m_walls[58].position = sf::Vector2f(150.f, 320.f);
    m_walls[59].position = sf::Vector2f(200.f, 320.f);
    m_walls[60].position = sf::Vector2f(200.f, 320.f);
    m_walls[61].position = sf::Vector2f(200.f, 370.f);
    m_walls[62].position = sf::Vector2f(200.f, 370.f);
    m_walls[63].position = sf::Vector2f(150.f, 370.f);
    m_walls[64].position = sf::Vector2f(150.f, 370.f);
    m_walls[65].position = sf::Vector2f(150.f, 320.f);
    //2
    m_walls[66].position = sf::Vector2f(150.f, 480.f);
    m_walls[67].position = sf::Vector2f(200.f, 480.f);
    m_walls[68].position = sf::Vector2f(200.f, 480.f);
    m_walls[69].position = sf::Vector2f(200.f, 530.f);
    m_walls[70].position = sf::Vector2f(200.f, 530.f);
    m_walls[71].position = sf::Vector2f(150.f, 530.f);
    m_walls[72].position = sf::Vector2f(150.f, 480.f);
    m_walls[73].position = sf::Vector2f(150.f, 530.f);
    
}

Map::~Map(){

}

// Accessors
///////////////////////////////////////////////////////////
// These functions access private variebles of class
///////////////////////////////////////////////////////////
sf::VertexArray Map::getWalls(){
    return m_walls;
}

void Map::update(){
    ///////////////////////////////////////////////////////////
    // This function currently does nothing (this function is for future)
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    // REMARKS:
    //      maybe add more features to game
}

void Map::render(sf::RenderTarget& target){
    ///////////////////////////////////////////////////////////
    // This function renders all lines
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      target - object to render to
    // OUTPUT:
    //      lines are rendered
    // REMARKS:
    target.draw(m_walls);
}