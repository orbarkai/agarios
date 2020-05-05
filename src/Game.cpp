#include "agarios/Game.h"
#include "services/Utils.h"
#include "services/Console.h"
#include "agarios/window.h"

Game::Game(GameConfig gameConfig)
    : gameConfig(gameConfig),
      players({}),
      foods({}) {

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
    for (int i = 0 ; i < 100; i++) {
        Food* food = new Food(this, sf::Vector2f(Utils::Math::randomFloat(0, 200), Utils::Math::randomFloat(0, 200)), Utils::Colors::randomColor());
        this->foods.push_back(food);
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
            playerI->second.update(inputI->second);
        }

        inputI++;
    }
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw grid
    this->drawGrid(target, states);

    // Draw foods 
    for(int i = 0; i != this->foods.size(); i++) {
        target.draw(*this->foods[i], states);
    }
    
    // Draw players
    Players::const_iterator it = this->players.begin();
    while (it != this->players.cend())
    {
        target.draw(it->second, states);

        it++;
    }
}

void Game::drawGrid(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vector2f topLeft = target.mapPixelToCoords({0, 0});
    sf::Vector2f bottomRight = target.mapPixelToCoords({(int)target.getSize().x, (int)target.getSize().y});

    for (float i = 0; i < bottomRight.x; i += this->gameConfig.GRID_MARGIN) {
        if (i >= topLeft.x) {
            sf::Vertex lineY[2];
            lineY[0].position = sf::Vector2f(i, topLeft.y);
            lineY[0].color  = sf::Color::White;
            lineY[1].position = sf::Vector2f(i, bottomRight.y);
            lineY[1].color = sf::Color::White;

            target.draw(lineY, 2, sf::Lines, states);
        }
    }


    for (float i = 0; i < bottomRight.y; i += this->gameConfig.GRID_MARGIN) {
        if (i >= topLeft.y) {
            sf::Vertex lineX[2];
            lineX[0].position = sf::Vector2f(topLeft.x, i);
            lineX[0].color  = sf::Color::White;
            lineX[1].position = sf::Vector2f(bottomRight.x, i);
            lineX[1].color = sf::Color::White;

            target.draw(lineX, 2, sf::Lines, states);
        }
    }
}

Player* Game::join()
{
    Player *player = new Player(this, {100, 100}, sf::Color::Cyan);
    this->players.insert({player->UUID, *player});
    return player;
}

void Game::removeFood(Food* food) {
    if (Utils::Arrays::includes<Food*>(this->foods, food)) {
        this->foods = Utils::Arrays::filter<Food*>(this->foods, [food](Food* Ifood) {
            return Ifood != food;
        });
        delete food;
    }
}

std::vector<Food*> Game::getFoods() const {
    return this->foods;
}