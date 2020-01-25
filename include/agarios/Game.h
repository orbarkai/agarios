#ifndef GAME_H_
#define GAME_H_

#include <unordered_map>
#include "agarios/Player.h"
#include "agarios/GameConfig.h"

class Window;

typedef std::unordered_map<std::string, sf::Vector2f> PlayersInput;
typedef std::unordered_map<std::string, Player> Players;

class Game : public sf::Drawable
{

    public:
        GameConfig gameConfig;

    private:
        Players players;

    public:
        Game(GameConfig gameConfig);

    public:
        void update(PlayersInput playersInput);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        Player* join();

};

#endif