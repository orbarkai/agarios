#include "agarios/window.h"
#include "services/Console.h"

Window::Window(Game* game)
               : sf::RenderWindow({game->gameConfig.WINDOW_WIDTH,
                                   game->gameConfig.WINDOW_HEIGHT},
                                   "Agarios")
               , GameObject(game) {

    this->setGame(game);

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

        this->setView(this->game->camera.getView());

        this->game->update({1, 0});

        this->draw(*this->game);

        this->display();
    }
}

void Window::setGame(Game* game) {
    if (this->game) this->game->window = NULL;
    this->game = game;
    this->game->window = this;
}

Game* Window::getGame() const{
    return this->game;
}