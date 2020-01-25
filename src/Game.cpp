#include "agarios/Game.h"
#include "services/Utils.h"
#include "services/Console.h"
#include "agarios/window.h"

Game::Game(GameConfig gameConfig)
    : gameConfig(gameConfig),
      players({}) {

        Console::startSection(Console::paint("magenta", "Game Config"));
        Console::log("Window Width",      "green") << gameConfig.WINDOW_WIDTH       << "px";
        Console::log("Window Height",     "green") << gameConfig.WINDOW_HEIGHT      << "px";
        Console::log("Camera Zoom",       "green") << gameConfig.CAMERA_ZOOM        << "x";
        Console::endSection();
        Console::log("Blob Initial Mass", "green") << gameConfig.BLOB_INITIAL_MASS;
        Console::log("Blob Shrink",       "green") << gameConfig.BLOB_SHRINK_FACTOR << "x";
        Console::log("Blob Speed",        "green") << gameConfig.BLOB_SPEED_FACTOR << "x";
        Console::endSection();

      }

void Game::update(PlayersInput playersInput)
{
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
    Players::const_iterator it = this->players.begin();
    while (it != this->players.cend())
    {
        target.draw(it->second, states);

        it++;
    }
}

Player *Game::join()
{
    Player *player = new Player(this, {100, 100}, sf::Color::Cyan);
    this->players.insert({player->UUID, *player});
    return player;
}