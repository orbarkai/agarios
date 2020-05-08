#include "agarios/Game.h"
#include "services/Utils.h"
#include "services/Console.h"
#include "agarios/window.h"
#include "agarios/Bot.h"


Game::Game(GameConfig gameConfig)
    : gameConfig(gameConfig),
      players({}),
      foods(QuadTree(sf::Rect({0, 0}, gameConfig.BOUNDS), 5)) {

    this->init();
}

void Game::init() {
// Log settings
    Console::startSection(Console::paint("magenta", "Game Config"));
    Console::log("Window Width",      "green") << gameConfig.WINDOW_WIDTH       << "px";
    Console::log("Window Height",     "green") << gameConfig.WINDOW_HEIGHT      << "px";
    Console::log("Camera Zoom",       "green") << gameConfig.CAMERA_ZOOM        << "x";
    Console::endSection();
    Console::log("Blob Initial Mass", "green") << gameConfig.BLOB_INITIAL_MASS;
    Console::log("Blob Shrink",       "green") << gameConfig.BLOB_SHRINK_FACTOR << "x";
    Console::log("Blob Speed",        "green") << gameConfig.BLOB_SPEED_FACTOR << "x";
    Console::endSection();

    // Generate foods
    for (int i = 0 ; i < this->gameConfig.FOOD_PER_PIXEL * (gameConfig.BOUNDS.x * gameConfig.BOUNDS.y); i++) {
        Food* food = new Food(this, this->randomPosition(), Utils::Colors::randomColor());
        this->foods.insert(food);
    }

    // Add bots
    for (int i = 0; i < 10; i++) {
        Bot* bot = new Bot(this, this->randomPosition(), Utils::Colors::randomColor());
        this->players.insert({bot->UUID, bot});
    }
}

void Game::update(PlayersInput playersInput)
{
    // Update players
    PlayersInput::iterator inputI = playersInput.begin();

    while (inputI != playersInput.end())
    {
        Players::iterator playerI = this->players.find(inputI->first);

        if (playerI != this->players.end())
        {
            playerI->second->update(inputI->second);
        }

        inputI++;
    }

    // update bots 
    Players::iterator playerI = this->players.begin();
    while (playerI != this->players.end()) {
        Player* player = playerI->second;
        Bot* bot = dynamic_cast<Bot*>(player);
        
        if (bot) {
            bot->update(bot->getNextMove().inputVelocity);
        }

        playerI++;
    }
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw grid
    this->drawGrid(target, states);

    // Draw foods 
    this->foods.forEach([&target, states](sf::Transformable* object) {
        Food* food = dynamic_cast<Food*>(object);
        if (food) {
            target.draw(*food, states);
        }
    });
    
    // Draw players
    Players::const_iterator it = this->players.begin();
    while (it != this->players.cend())
    {
        target.draw(*it->second, states);

        it++;
    }
}

void Game::drawGrid(sf::RenderTarget& target, sf::RenderStates states) const {
    float margin = (float)(1 + ((int)target.getView().getSize().x / 100)) * this->gameConfig.GRID_MARGIN;

    // Vertical lines
    for (float i = 0; i <= this->gameConfig.BOUNDS.x; i += margin) {
        sf::Vertex lineY[2];
        lineY[0].position = sf::Vector2f(i, 0);
        lineY[0].color  = sf::Color::White;
        lineY[1].position = sf::Vector2f(i, this->gameConfig.BOUNDS.y);
        lineY[1].color = sf::Color::White;

        target.draw(lineY, 2, sf::Lines, states);
    }


    // Hoeizontal lines
    for (float i = 0; i <= this->gameConfig.BOUNDS.y; i += margin) {
        sf::Vertex lineX[2];
        lineX[0].position = sf::Vector2f(0, i);
        lineX[0].color  = sf::Color::White;
        lineX[1].position = sf::Vector2f(this->gameConfig.BOUNDS.x, i);
        lineX[1].color = sf::Color::White;

        target.draw(lineX, 2, sf::Lines, states);
    }

    // Bounding
    sf::RectangleShape boundingShape = sf::RectangleShape(this->gameConfig.BOUNDS);
    boundingShape.setFillColor(sf::Color::Transparent);
    boundingShape.setOutlineColor(sf::Color::White);
    boundingShape.setOutlineThickness(5);
    target.draw(boundingShape, states);
}

Player* Game::join()
{
    Player *player = new Player(this, {100, 100}, sf::Color::Cyan);
    this->players.insert({player->UUID, player});
    Console::log(player->UUID) << "joined";
    return player;
}

void Game::removeFood(Food* food) {
    if (this->foods.remove(food)) {
        delete food;

         // Generate a new food
        Food* newFood = new Food(this, this->randomPosition(), Utils::Colors::randomColor());
        this->foods.insert(newFood);
    }
}

QuadTree Game::getFoods() const {
    return this->foods;
}

sf::Vector2f Game::randomPosition() const {
    sf::Vector2f pos = Utils::Vectors::randomVector();
    sf::Vector2f bounds = this->gameConfig.BOUNDS;
    Utils::Vectors::mult(pos, bounds);
    return pos;
}