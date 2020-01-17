#ifndef GAME_H_
#define GAME_H_

#include "agarios/Player.h"
#include "agarios/GameConfig.h"
#include "agarios/Camera.h"

class Window;

class Game : public sf::Drawable
{

    public:
        GameConfig gameConfig;
        Camera camera;
        Window* window;

    private:
        std::vector<Player> players;
        Player* mainPlayer;
       

    public:
        Game(GameConfig gameConfig, bool initiateMainPlayer);

    public:
        void update(sf::Vector2f inputVelocity);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::Vector2u getWindowSize() const;

        Player* getMainPlayer();
        void setMainPlayer(Player player);

};

#endif