#include "agarios/Game.h"
#include "services/Utils.h"
#include "services/Console.h"

Game::Game(GameConfig* gameConfig, bool initiateMainPlayer)
          : GameObject(gameConfig),
            players(std::vector<Player>()) {

    if (initiateMainPlayer) {
        Player* mainPlayer = new Player(gameConfig, {100, 100}, sf::Color::Cyan);
        this->players.push_back(*mainPlayer);
        this->mainPlayer = mainPlayer;
    } else {
        this->mainPlayer = NULL;
    }

}

Player* Game::getMainPlayer() {
    return this->mainPlayer;
}

void Game::setMainPlayer(Player player) {
    if (Utils::Arrays::includes<Player>(this->players, player)) {
        this->mainPlayer = &player;
    }
}

void Game::update(sf::Vector2f inputVelocity) {
    for (int i = 0; i < this->players.size(); i++) {
        if (this->players[i] == *this->mainPlayer) {
            this->players[i].update(inputVelocity);
        } else {
            this->players[i].update({0, 0});
        }
    }
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int i = 0; i < this->players.size(); i++) {
        target.draw(this->players[i], states);
    }
}