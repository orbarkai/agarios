#include "agarios/Game.h"
#include "services/Utils.h"
#include "services/Console.h"
#include "agarios/window.h"

Game::Game(GameConfig gameConfig)
    : gameConfig(gameConfig),
      players({}) {}

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