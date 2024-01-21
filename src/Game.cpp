#include "Classes/Game.h"

// Private functions
void Game::initWindow(){
    ///////////////////////////////////////////////////////////
    // This function initialize window
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		window is initialized
    // REMARKS:

    // Make unique, set size of window, title, style
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800,600), "Simple 2D Shooter", sf::Style::Close | sf::Style::Titlebar);

    // Set framerate limit
    m_window->setFramerateLimit(60);
}

void Game::initVariables(){
    ///////////////////////////////////////////////////////////
    // This function initialize variables
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		private vairbles are initialized
    // REMARKS:

    m_startGame = true;
    m_endGame = false;
    m_playerDetected = false;
    m_collectedStars = 0;
}

void Game::initFont(){
    ///////////////////////////////////////////////////////////
    // This function loads font from file
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		font is/is not loaded
    // REMARKS:

    // Check if font is loaded if not print message to consol
    if(!m_font.loadFromFile("../../Fonts/Pixellettersfull.ttf"))
        std::cout << "Error loading font!" << std::endl;
}

void Game::initTexts(){
    ///////////////////////////////////////////////////////////
    // This function initialize texts
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		texts are initialized
    // REMARKS:

    // Set parameters to start text
    m_startText.setFont(m_font);
    m_startText.setFillColor(sf::Color::White);
    m_startText.setCharacterSize(60);
    m_startText.setPosition(sf::Vector2f(100.f, 200.f));
    m_startText.setString("Welcome to Sneak and Shoot!\n  Press Enter to start game...");

    // Set parameters to end text
    m_endText.setFont(m_font);
    m_endText.setFillColor(sf::Color::White);
    m_endText.setCharacterSize(60);
    m_endText.setPosition(sf::Vector2f(150.f, 200.f));
}

void Game::initMouse(){
    ///////////////////////////////////////////////////////////
    // This function initialize mouse
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		mouse is initialized
    // REMARKS:

    // Set mouse position and relative to window
    m_mouse.setPosition(sf::Vector2i(400, 200), *m_window);

    // Get mouse position and assign it to its own variable
    m_mousePosition = sf::Vector2i(m_mouse.getPosition(*m_window));
}

void Game::initEntities(){
    ///////////////////////////////////////////////////////////
    // This function initialize all entities (player, map, enemies, stars)
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		entites are initialized
    // REMARKS:

    // Map initialization
    m_map = std::make_unique<Map>();

    // Player initialization
    m_player = std::make_unique<Player>();
    
    // Initialize and push back guards
    m_guards.push_back(std::make_unique<Guard>(GUARD_1));
    m_guards.push_back(std::make_unique<Guard>(GUARD_2));
    m_guards.push_back(std::make_unique<Guard>(GUARD_3));

    // Initialize and push back counterterrotists
    m_counterterrorists.push_back(std::make_unique<Counterterrorist>(COUNTERTERRORIST_1));
    m_counterterrorists.push_back(std::make_unique<Counterterrorist>(COUNTERTERRORIST_2));
    m_counterterrorists.push_back(std::make_unique<Counterterrorist>(COUNTERTERRORIST_3));
    m_counterterrorists.push_back(std::make_unique<Counterterrorist>(COUNTERTERRORIST_4));

    // Initialize and push back specialforce
    m_specialforces.push_back(std::make_unique<Specialforce>(SPECIALFORCE));

    // Initialize and push back stars
    m_stars.push_back(std::make_unique<Star>(sf::Vector2f(200.f, 42.5f)));
    m_stars.push_back(std::make_unique<Star>(sf::Vector2f(475.f, 270.f)));
    m_stars.push_back(std::make_unique<Star>(sf::Vector2f(735.f, 370.f)));

    // Initialize and push back finish star
    m_finishStar = std::make_unique<FinishStar>(sf::Vector2f(360.f, 260.f));

    // Loop through guards and push back pointer to vector were enemies are stored
    for(auto &guard : m_guards){
        m_enemies.push_back(std::move(guard));
    }

    // Loop through counterterrorists and push back pointer to vector were enemies are stored
    for(auto &counterterrorist : m_counterterrorists){
        m_enemies.push_back(std::move(counterterrorist));
    }

    // Loop through specialforces and push back pointer to vector were enemies are stored
    for(auto &specialforce : m_specialforces){
        m_enemies.push_back(std::move(specialforce));
    }
}


// Constructor and Destructor
Game::Game(){
    ///////////////////////////////////////////////////////////
    // This is class constructor
    ///////////////////////////////////////////////////////////

    this->initVariables();
    this->initWindow();
    this->initFont();
    this->initTexts();
    this->initMouse();
    this->initEntities();
}

Game::~Game(){

}

// Functions
void Game::run(){
    ///////////////////////////////////////////////////////////
    // This function runs main loops
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		main loops
    // REMARKS:

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
    ///////////////////////////////////////////////////////////
    // This function reset all entites and calls initEntites and initMouse
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		game is reseted
    // REMARKS:

    // Clear all enemies vectors
    m_enemies.clear();
    m_guards.clear();
    m_counterterrorists.clear();
    m_specialforces.clear();

    // Clear star vector
    m_stars.clear();

    m_map.reset();

    m_player.reset();

    m_finishStar.reset();

    this->initMouse();
    this->initEntities();
}

void Game::renderStartScreen(){
    ///////////////////////////////////////////////////////////
    // This function renders start screen
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		start screen is rendered
    // REMARKS:

    m_window->clear(sf::Color::Black);
    m_window->draw(m_startText);
    m_window->display();
}

void Game::renderEndScreen(){
    ///////////////////////////////////////////////////////////
    // This function renders end screen
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		end screen is rendered
    // REMARKS:
    m_window->clear(sf::Color::Black);
    m_window->draw(m_endText);
    m_window->display();
}

void Game::pollEvents(){
    ///////////////////////////////////////////////////////////
    // This function polls events in game
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		start screen is rendered
    // REMARKS:
    //      checks all events that are happening in game
    //      for e.g mouse is moved or key is pressed
    //      and acts accordingly

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
    ///////////////////////////////////////////////////////////
    // This function checks if bullet is colliding with map (calls bulletWallIntersection)
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      bullet - reference to object of class Bullet
    // OUTPUT:
    //		boolean
    // REMARKS:

    // Get four points of rectangle shape (class Bullet)
    std::vector<sf::Vector2f> points = bullet.getPoints();

    // Get lines from map
    sf::VertexArray walls = m_map->getWalls();

    // Iterate through the line segments
    for (std::size_t i = 0; i < walls.getVertexCount() - 1; i+=2) {
        sf::Vector2f lineStart = walls[i].position;
        sf::Vector2f lineEnd = walls[i + 1].position;

        // Check if any rectangle side intersects with the line segment if so return true
        if (this->bulletWallIntersection(points[0], points[2], lineStart, lineEnd) ||
            this->bulletWallIntersection(points[1], points[3], lineStart, lineEnd) ||
            this->bulletWallIntersection(points[0], points[1], lineStart, lineEnd) ||
            this->bulletWallIntersection(points[2], points[3], lineStart, lineEnd)){
            return true;
        }
    }
    // If not return false
    return false; 
}

bool Game::bulletWallIntersection(sf::Vector2f& p1, sf::Vector2f& p2, sf::Vector2f& p3, sf::Vector2f& p4){
    ///////////////////////////////////////////////////////////
    // This function checks collision of two lines
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      p1 - first point of first line
    //      p2 - second point of first line
    //      p3 - first point of second line
    //      p4 - second point of seconf line
    // OUTPUT:
    //		boolean
    // REMARKS:
    //      source: wikipedia 
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
    ///////////////////////////////////////////////////////////
    // This function checks if particular enemy is hit
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      enemy - reference to object of class Enemy
    // OUTPUT:
    //		boolean
    // REMARKS:

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
    ///////////////////////////////////////////////////////////
    // This function checks player's intersection with stars
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		boolean
    // REMARKS:

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
    ///////////////////////////////////////////////////////////
    // This function check player's intersection with finish star
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		start screen is rendered
    // REMARKS:
    if(m_player->getGlobalBounds().intersects(m_finishStar->getBounds()))
        m_endGame = true;
}

void Game::checkEraseEnemy(){
    ///////////////////////////////////////////////////////////
    // This function checks if enemy is dead and erase if so
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		enemy is/is not erased
    // REMARKS:

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
    ///////////////////////////////////////////////////////////
    // This function shoots bullets
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		bullet is fired
    // REMARKS:

    sf::Vector2f playerPosition = m_player->getPosition() + sf::Vector2f(m_player->getRadius(), m_player->getRadius());
    sf::Vector2f playerDirection = m_player->getDirection();
    sf::Vector2f diff = sf::Vector2f(static_cast<float>(m_mousePosition.x), static_cast<float>(m_mousePosition.y)) - playerPosition;

    float angle = atan2(diff.y, diff.x);
    float currAngle = atan2(playerDirection.y, playerDirection.x);

    m_bullets.push_back(std::make_unique<Bullet>(playerPosition,currAngle));
}

void Game::updateStars(){
    ///////////////////////////////////////////////////////////
    // This function updates stars
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		increment/do not increment collected stars
    // REMARKS:

    if(this->collectStar()){
        ++m_collectedStars;
    }
}

void Game::updateBullets() {
    ///////////////////////////////////////////////////////////
    // This function updates bullets
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		bullet is updated
    // REMARKS:

    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(),
        [this](const std::unique_ptr<Bullet>& bullet) {
            bullet->update();
            return this->bulletMapCollision(*bullet);
        }),
        m_bullets.end()
    );
}

void Game::updateEnemies(sf::VertexArray& walls){
    ///////////////////////////////////////////////////////////
    // This function updates enemies
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    //      walls - lines (two vertices) representing map
    // OUTPUT:
    //		enemies are updated
    // REMARKS:

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
    ///////////////////////////////////////////////////////////
    // This function updates all entities by calling coresponding functions
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		game is updated
    // REMARKS:

    sf::VertexArray walls = m_map->getWalls();      
    m_player->update(walls, m_mousePosition);
    this->updateEnemies(walls);
    this->updateBullets();
    this->updateStars();
    this->isWon();
}

void Game::renderBullets(){
    ///////////////////////////////////////////////////////////
    // This function renders bullets
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		bullets are rendered
    // REMARKS:

    for(auto &bullet : m_bullets){
        bullet->render(*m_window);
    }
}

void Game::renderEnemies(){
    ///////////////////////////////////////////////////////////
    // This function renders enemies
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		enemies are rendered
    // REMARKS:

    for(auto &enemy : m_enemies){
        enemy->render(*m_window);
    }
}

void Game::renderStars(){
    ///////////////////////////////////////////////////////////
    // This function renders stars
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		stars are rendered
    // REMARKS:

    for(auto &star : m_stars){
        star->render(*m_window);
    }
}

void Game::render(){
    ///////////////////////////////////////////////////////////
    // This function renders all entities by calling coresponding functions
    ///////////////////////////////////////////////////////////
    //		
    // INPUT:
    // OUTPUT:
    //		game is rendered
    // REMARKS:
    
    m_window->clear(sf::Color::Black);

    m_map->render(*m_window);
    this->renderStars();
    m_finishStar->render(*m_window);
    this->renderEnemies();
    this->renderBullets();
    
    m_player->render(*m_window);

    m_window->display();
}