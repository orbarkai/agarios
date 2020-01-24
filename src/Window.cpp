#include "agarios/window.h"
#include "services/Console.h"

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

        this->game->update({{this->mainPlayer->UUID, {1, 0}}});

        this->draw(*this->game);

        this->display();
    }
}

void Window::setGame(Game* game) {
    this->game = game;
}

Game* Window::getGame() const{
    return this->game;
}

Player* Window::getMainPlayer() {
    return this->mainPlayer;
}

void Window::setMainPlayer(Player* player) {
    this->mainPlayer = player;
    if (this->mainPlayer) {
        this->camera.setTarget(this->mainPlayer);
    }
}