#ifndef GAME_H_
#define GAME_H_

#include <unordered_map>
#include "agarios/Player.h"
#include "agarios/GameConfig.h"
#include "agarios/gameObjects/Food.h"

class Window;

typedef std::unordered_map<std::string, sf::Vector2f> PlayersInput;
typedef std::unordered_map<std::string, Player> Players;

class Game : public sf::Drawable
{

    public:
        GameConfig gameConfig;

    private:
        Players players;
        std::vector<Food*> foods;

    public:
        Game(GameConfig gameConfig);

    public:
        void update(PlayersInput playersInput);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void init();

        Player* join();
        void removeFood(Food* food);

        std::vector<Food*> getFoods() const;

        sf::Vector2f randomPosition() const;

    private:
        void drawGrid(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif