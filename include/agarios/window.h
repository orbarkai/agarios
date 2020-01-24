#ifndef WINDOW_H_
#define WINDOW_H_

#include "SFML/Graphics.hpp"
#include "agarios/Game.h"
#include "agarios/Camera.h"

class Window : public sf::RenderWindow, private GameObject
{

    friend class Camera;

    private:
        Player* mainPlayer;
        Camera camera;

    public:
        Window(Game* game, Player* mainPlayer);

    public:
        void run();

    public:
        void setGame(Game* game);
        Game* getGame() const;

        Player* getMainPlayer();
        void setMainPlayer(Player* player);

};

#endif