#include "Classes/Game.h"

void Game::initWindow(){
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800,600), "Simple 2D Shooter", sf::Style::Close | sf::Style::Titlebar);
    m_window->setFramerateLimit(60);
}

void Game::initVariables(){
    m_startGame = true;
    m_endGame = false;
    m_playerDetected = false;
    m_collectedStars = 0;
}

void Game::initFont(){
    if(!m_font.loadFromFile("../../Fonts/Pixellettersfull.ttf"))
        std::cout << "Error loading font!" << std::endl;
}

void Game::initTexts(){
    m_startText.setFont(m_font);
    m_startText.setFillColor(sf::Color::White);
    m_startText.setCharacterSize(60);
    m_startText.setPosition(sf::Vector2f(100.f, 200.f));
    m_startText.setString("Welcome to Sneak and Shoot!\n  Press Enter to start game...");

    m_endText.setFont(m_font);
    m_endText.setFillColor(sf::Color::White);
    m_endText.setCharacterSize(60);
    m_endText.setPosition(sf::Vector2f(150.f, 200.f));
}

void Game::initMouse(){
    m_mouse.setPosition(sf::Vector2i(400, 200), *m_window);
    m_mousePosition = sf::Vector2i(m_mouse.getPosition(*m_window));
}

void Game::initEntities(){
    m_map = std::make_unique<Map>();

    m_player = std::make_unique<Player>();
    
    m_guards.push_back(std::make_unique<Guard>(GUARD_1));
    m_guards.push_back(std::make_unique<Guard>(GUARD_2));
    m_guards.push_back(std::make_unique<Guard>(GUARD_3));

    m_counterterrorists.push_back(std::make_unique<Counterterrorist>(COUNTERTERRORIST_1));
    m_counterterrorists.push_back(std::make_unique<Counterterrorist>(COUNTERTERRORIST_2));
    m_counterterrorists.push_back(std::make_unique<Counterterrorist>(COUNTERTERRORIST_3));
    m_counterterrorists.push_back(std::make_unique<Counterterrorist>(COUNTERTERRORIST_4));

    m_specialforces.push_back(std::make_unique<Specialforce>(SPECIALFORCE));

    m_stars.push_back(std::make_unique<Star>(sf::Vector2f(200.f, 42.5f)));
    m_stars.push_back(std::make_unique<Star>(sf::Vector2f(475.f, 270.f)));
    m_stars.push_back(std::make_unique<Star>(sf::Vector2f(735.f, 370.f)));

    m_finishStar = std::make_unique<FinishStar>(sf::Vector2f(360.f, 260.f));

    for(auto &guard : m_guards){
        m_enemies.push_back(std::move(guard));
    }

    for(auto &counterterrorist : m_counterterrorists){
        m_enemies.push_back(std::move(counterterrorist));
    }

    for(auto &specialforce : m_specialforces){
        m_enemies.push_back(std::move(specialforce));
    }
}

Game::Game(){
    this->initVariables();
    this->initWindow();
    this->initFont();
    this->initTexts();
    this->initMouse();
    this->initEntities();
}

Game::~Game(){

}

void Game::run(){
    while(m_window->isOpen()){
        while(m_startGame && m_window->isOpen()){
            this->renderStartScreen();
            this->pollEvents();
        }
        while(m_endGame && m_window->isOpen()){
            if(m_playerDetected){
                m_endText.setString("\t\tGame Over!\n You have been detected!\n  Press R to start again...");
            }
            else{
                m_endText.setString("Congratulations! You won!\nPress R to start again...");
            }
            this->renderEndScreen();
            this->pollEvents();
        }
        this->pollEvents();
        this->update();
        this->render();

    }
}

void Game::reset(){
    m_enemies.clear();
    m_guards.clear();
    m_counterterrorists.clear();
    m_specialforces.clear();

    m_stars.clear();

    m_map.reset();

    m_player.reset();

    m_finishStar.reset();

    this->initMouse();
    this->initEntities();
}

void Game::renderStartScreen(){
    m_window->clear(sf::Color::Black);
    m_window->draw(m_startText);
    m_window->display();
}

void Game::renderEndScreen(){
    m_window->clear(sf::Color::Black);
    m_window->draw(m_endText);
    m_window->display();
}

void Game::pollEvents(){
    while(m_window->pollEvent(m_sfmlEvent)){
        switch (m_sfmlEvent.type)
        {
        case sf::Event::Closed:
            m_window->close();
            break;
        case sf::Event::KeyPressed:
            if(m_sfmlEvent.key.code == sf::Keyboard::Escape){
                m_window->close();
            }
            else if(m_sfmlEvent.key.code == sf::Keyboard::Enter){
                m_startGame = false;
            }
            else if(m_sfmlEvent.key.code == sf::Keyboard::R && m_endGame){
                m_endGame = false;
                m_playerDetected = false;
                this->reset();
            }
            break;
        case sf::Event::MouseMoved:
            m_mousePosition = sf::Vector2i(m_mouse.getPosition(*m_window));
            break;
        case sf::Event::MouseButtonPressed:
            if(m_sfmlEvent.mouseButton.button == sf::Mouse::Left && m_player->canshoot())
                this->shootBullet();
            break;
        default:
            break;
        }
    }
}

bool Game::bulletMapCollision(Bullet& bullet){
    std::vector<sf::Vector2f> points = bullet.getPoints();

    sf::VertexArray walls = m_map->getWalls();
    // Iterate through the line segments
    for (std::size_t i = 0; i < walls.getVertexCount() - 1; i+=2) {
        sf::Vector2f lineStart = walls[i].position;
        sf::Vector2f lineEnd = walls[i + 1].position;

        // Check if any rectangle side intersects with the line segment
        if (this->bulletWallIntersection(points[0], points[2], lineStart, lineEnd) ||
            this->bulletWallIntersection(points[1], points[3], lineStart, lineEnd) ||
            this->bulletWallIntersection(points[0], points[1], lineStart, lineEnd) ||
            this->bulletWallIntersection(points[2], points[3], lineStart, lineEnd)){
            return true; // Intersection detected
        }
    }
    return false; // No intersection detected
}

bool Game::bulletWallIntersection(sf::Vector2f& p1, sf::Vector2f& p2, sf::Vector2f& p3, sf::Vector2f& p4) {
    float denominator = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);

    // Check if the lines are not parallel
    if (denominator != 0.f) {
        float ua = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) / denominator;
        float ub = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) / denominator;

        // Check if the intersection point is within both line segments
        if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1) {
            return true;
        }
    }
    return false;
}

bool Game::isHitEnemy(Enemy& enemy){
    sf::FloatRect enemyBounds = enemy.getBounds();
    auto it = m_bullets.begin();
    while (it != m_bullets.end()){
        sf::FloatRect bulletBounds = (*it)->getBounds();
        if (enemyBounds.intersects(bulletBounds)){
            it = m_bullets.erase(it);
            return true;
        } 
        else{
             ++it;
        }
    }
    return false;
}

bool Game::collectStar(){
    sf::FloatRect playerBounds = m_player->getGlobalBounds();
    auto it = m_stars.begin();
    while (it != m_stars.end()){
        sf::FloatRect starBounds = (*it)->getBounds();
        if (playerBounds.intersects(starBounds)){
            it = m_stars.erase(it);
            return true;
        } 
        else{
             ++it;
        }
    }
    return false;
}

void Game::isWon(){
    if(m_player->getGlobalBounds().intersects(m_finishStar->getBounds()))
        m_endGame = true;
}

void Game::checkEraseEnemy(){
    auto it = m_enemies.begin();
    while (it != m_enemies.end()) {
        if ((*it)->isDead()) {
            it = m_enemies.erase(it);
        } else {
             ++it;
        }
    }
}

void Game::shootBullet(){
    sf::Vector2f playerPosition = m_player->getPosition() + sf::Vector2f(m_player->getRadius(), m_player->getRadius());
    sf::Vector2f playerDirection = m_player->getDirection();
    sf::Vector2f diff = sf::Vector2f(static_cast<float>(m_mousePosition.x), static_cast<float>(m_mousePosition.y)) - playerPosition;

    float angle = atan2(diff.y, diff.x);
    float currAngle = atan2(playerDirection.y, playerDirection.x);

    m_bullets.push_back(std::make_unique<Bullet>(playerPosition,currAngle));
}

void Game::updateStars(){
    if(this->collectStar()){
        ++m_collectedStars;
    }
}

void Game::updateBullets() {
    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(),
        [this](const std::unique_ptr<Bullet>& bullet) {
            bullet->update();
            return this->bulletMapCollision(*bullet);
        }),
        m_bullets.end()
    );
}

void Game::updateEnemies(sf::VertexArray& walls){
    for(auto &enemy : m_enemies){
        enemy->update(walls, m_player->getPosition(), m_player->getRadius());
        if(this->isHitEnemy(*enemy)){
            enemy->gotShot();
        }
        if(enemy->getIsPlayerDetected()){
            m_playerDetected = true;
            m_endGame = true;
        }
    }
    this->checkEraseEnemy();
}

void Game::update(){
    sf::VertexArray walls = m_map->getWalls();      
    m_player->update(walls, m_mousePosition);
    this->updateEnemies(walls);
    this->updateBullets();
    this->updateStars();
    this->isWon();
}

void Game::renderBullets(){
    for(auto &bullet : m_bullets){
        bullet->render(*m_window);
    }
}

void Game::renderEnemies(){
    for(auto &enemy : m_enemies){
        enemy->render(*m_window);
    }
}

void Game::renderStars(){
    for(auto &star : m_stars){
        star->render(*m_window);
    }
}

void Game::render(){
    m_window->clear(sf::Color::Black);

    m_map->render(*m_window);
    this->renderStars();
    m_finishStar->render(*m_window);
    this->renderEnemies();
    this->renderBullets();
    
    m_player->render(*m_window);

    m_window->display();
}