#pragma once

#include "Classes/Map.h"
#include "Classes/Player.h"
#include "Classes/Enemy.h"
#include "Classes/Guard.h"
#include "Classes/Counterterrorist.h"
#include "Classes/Specialforce.h"
#include "Classes/Bullet.h"
#include "Classes/Star.h"
#include "Classes/FinishStar.h"
#include <iostream>

class Game{
private:
    std::unique_ptr<sf::RenderWindow> m_window;
    sf::Event m_sfmlEvent;
    bool m_startGame;
    bool m_endGame;
    bool m_playerDetected;
    int m_collectedStars;
    //map
    std::unique_ptr<Map> m_map;
    
    //mouse
    sf::Mouse m_mouse;
    sf::Vector2i m_mousePosition;

    //player
    std::unique_ptr<Player> m_player;

    //vector of shared pointers to class Enemy
    std::vector<std::unique_ptr<Enemy>> m_enemies;

    //vector of objects of class Guard
    std::vector<std::unique_ptr<Guard>> m_guards;

    //vector of objects of class Counterterrorist
    std::vector<std::unique_ptr<Counterterrorist>> m_counterterrorists;

    //vector of objects of class Counterterrorist
    std::vector<std::unique_ptr<Specialforce>> m_specialforces;

    //vector of bullets
    std::vector<std::unique_ptr<Bullet>> m_bullets;

    //vector of Stars
    std::vector<std::unique_ptr<Star>> m_stars;

    //finish star
    std::unique_ptr<FinishStar> m_finishStar;

    //font anf text
    sf::Font m_font;
    sf::Text m_startText;
    sf::Text m_endText;

    void initVariables();
    void initWindow();
    void initFont();
    void initTexts();
    void initMouse();
    void initEntities();
public:
    Game();
    virtual ~Game();

    void run();
    void reset();
    void renderStartScreen();
    void renderEndScreen();
    void pollEvents();

    bool bulletMapCollision(Bullet& bullet);
    bool bulletWallIntersection(sf::Vector2f& p1, sf::Vector2f& p2, sf::Vector2f& p3, sf::Vector2f& p4);
    bool isHitEnemy(Enemy& enemy);
    bool collectStar();
    void isWon();
    void checkEraseEnemy();
    void shootBullet();
    void updateStars();
    void updateBullets();
    void updateEnemies(sf::VertexArray& walls);
    void update();
    void renderBullets();
    void renderEnemies();
    void renderStars();
    void render();
};