#include "agarios/Game.h"

#include "services/Utils.h"
#include "services/Console.h"

#include "agarios/window.h"

Game::Game(GameConfig gameConfig, bool initiateMainPlayer)
          : gameConfig(gameConfig),
            players(std::vector<Player>()),
            camera(this, NULL) {

    if (initiateMainPlayer) {
        Player* mainPlayer = new Player(this, {100, 100}, sf::Color::Cyan);
        this->players.push_back(*mainPlayer);
        this->mainPlayer = mainPlayer;
        this->camera.setTarget(mainPlayer);
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
        this->camera.setTarget(this->mainPlayer);
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

sf::Vector2u Game::getWindowSize() const {
    if (this->window) return this->window->getSize();
    
    return {(unsigned int)this->gameConfig.WINDOW_WIDTH, 
            (unsigned int)this->gameConfig.WINDOW_HEIGHT};
}