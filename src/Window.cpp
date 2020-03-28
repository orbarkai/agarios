#include "agarios/window.h"
#include "services/Console.h"
#include "services/Utils.h"


Window::Window(Game* game, Player* mainPlayer=NULL)
               : sf::RenderWindow({game->gameConfig.WINDOW_WIDTH,
                                   game->gameConfig.WINDOW_HEIGHT},
                                   "Agarios")
               , GameObject(game)
               , camera(this, NULL) {

    this->setGame(game);
    this->setMainPlayer(mainPlayer);

    if (this->game && !this->mainPlayer) {
        this->setMainPlayer(this->game->join());
    }
}

void Window::run() {
    this->setFramerateLimit(60);

    while (this->isOpen())
    {
        sf::Event event;
        while (this->pollEvent(event))
        {
            // Request for closing the window
            if (event.type == sf::Event::Closed)
                this->close();
        }

        this->clear();

        this->setView(this->camera.getView());

        this->getPlayerInput();

        this->game->update({{this->mainPlayer->UUID, this->getPlayerInput()}});

        this->draw(*this->game);

        this->display();
    }
}

void Window::setGame(Game* const game) {
    this->game = game;
}

Game* Window::getGame() const {
    return this->game;
}

Player* Window::getMainPlayer() const {
    return this->mainPlayer;
}

void Window::setMainPlayer(Player* const player) {
    this->mainPlayer = player;
    if (this->mainPlayer) {
        this->camera.setTarget(this->mainPlayer);
    }
}

sf::Vector2f Window::getPlayerInput() {
    sf::Vector2i center = {(float)this->getSize().x / 2.0, (float)this->getSize().y / 2.0};
    sf::Vector2i mouse = sf::Mouse::getPosition(*this);

    sf::Vector2f input = {mouse.x - center.x, mouse.y - center.y};
    float maxRadius = (float)std::min<unsigned int>(this->getSize().x, this->getSize().y) * 0.3;

    Utils::Vectors::limit(input, maxRadius);
    input /= maxRadius;
    
    return input;
}