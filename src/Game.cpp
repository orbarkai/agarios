#include "agarios/Game.h"
#include "services/Utils.h"
#include "services/Console.h"
#include "services/FS.h"
#include "agarios/Bot.h"

std::vector<std::string> Game::names = FS::getJsonResource("names.json");

Game::Game(GameConfig gameConfig, Window* window)
    : gameConfig(gameConfig),
      window(window),
      players({}),
      foods(QuadTree(gameConfig.BOUNDS, 10)) {
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
    for (int i = 0 ; i < this->gameConfig.FOOD_PER_PIXEL * (gameConfig.BOUNDS.width * gameConfig.BOUNDS.height); i++) {
        Food* food = new Food(this,  this->randomPosition(), Utils::Colors::randomColor());
        this->foods.insert(food);
    }

    // Add bots
    for (int i = 0; i < 10; i++) {
        Bot* bot = new Bot(this, this->randomPosition(), Utils::Colors::randomColor());
        this->players.insert({bot->UUID, bot});
    }
}

void Game::update(PlayersInput playersInput, Window* window)
{
    // Update players
    PlayersInput::iterator inputI = playersInput.begin();

    while (inputI != playersInput.end())
    {
        Players::iterator playerI = this->players.find(inputI->first);

        if (playerI != this->players.end())
        {
            playerI->second->update(inputI->second, window);
        }

        inputI++;
    }

    // update bots 
    Players::iterator playerI = this->players.begin();
    while (playerI != this->players.end()) {
        Player* player = playerI->second;
        Bot* bot = dynamic_cast<Bot*>(player);
        
        if (bot) {
            bot->update(bot->getNextMove().inputVelocity, window);
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
    if (this->gameConfig.GRID_MODE == GameConfig::GridMode::SYMETRIC) {
        float margin = (float)(1 + ((int)target.getView().getSize().x / 100)) * this->gameConfig.GRID_MARGIN;

        // Vertical lines
        for (float i = this->gameConfig.BOUNDS.left; i <= this->gameConfig.BOUNDS.left + this->gameConfig.BOUNDS.width; i += margin) {
            sf::Vertex lineY[2];
            lineY[0].position = sf::Vector2f(i, this->gameConfig.BOUNDS.top);
            lineY[0].color  = sf::Color::White;
            lineY[1].position = sf::Vector2f(i, this->gameConfig.BOUNDS.top + this->gameConfig.BOUNDS.height);
            lineY[1].color = sf::Color::White;

            target.draw(lineY, 2, sf::Lines, states);
        }


        // Hoeizontal lines
        for (float i = this->gameConfig.BOUNDS.top; i <= this->gameConfig.BOUNDS.top + this->gameConfig.BOUNDS.height; i += margin) {
            sf::Vertex lineX[2];
            lineX[0].position = sf::Vector2f(this->gameConfig.BOUNDS.left, i);
            lineX[0].color  = sf::Color::White;
            lineX[1].position = sf::Vector2f(this->gameConfig.BOUNDS.left + this->gameConfig.BOUNDS.width, i);
            lineX[1].color = sf::Color::White;

            target.draw(lineX, 2, sf::Lines, states);
        }
    } else if (this->gameConfig.GRID_MODE == GameConfig::GridMode::QUADTREE) {
        this->foods.draw(target, states);
    }

    // Bounding
    sf::RectangleShape boundingShape = sf::RectangleShape({this->gameConfig.BOUNDS.width, this->gameConfig.BOUNDS.height});
    boundingShape.setPosition(this->gameConfig.BOUNDS.left, this->gameConfig.BOUNDS.top);
    boundingShape.setFillColor(sf::Color::Transparent);
    boundingShape.setOutlineColor(sf::Color::White);
    boundingShape.setOutlineThickness(5);
    target.draw(boundingShape, states);
}

Player* Game::join()
{
    Player *player = new Player(this, {100, 100}, sf::Color::Cyan);
    this->players.insert({player->UUID, player});
    Console::log(player->getLoggerName()) << "joined";
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

void Game::setWindow(Window* const window) {
    this->window = window;
}

Window* Game::getWindow() const {
    return this->window;
}

sf::Vector2f Game::randomPosition() const {
    sf::Vector2f pos = Utils::Vectors::randomVector();
    sf::Vector2f boundsSize = {this->gameConfig.BOUNDS.width, this->gameConfig.BOUNDS.height};
    Utils::Vectors::mult(pos, boundsSize);
    pos += {this->gameConfig.BOUNDS.left, this->gameConfig.BOUNDS.top};
    return pos;
}

std::string Game::randomName() const {
    std::string name = Game::names[rand() % Game::names.size()];
    return name;
}
