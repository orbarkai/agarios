#ifndef WINDOW_H_
#define WINDOW_H_

#include "SFML/Graphics.hpp"
#include "agarios/Game.h"

class Window : public sf::RenderWindow, private GameObject
{

    public:
        Window(Game* game);

    public:
        void run();

    public:
        void setGame(Game* game);
        Game* getGame() const;

};

#endif