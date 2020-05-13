#ifndef GAME_H_
#define GAME_H_

#include <unordered_map>
#include "agarios/Player.h"
#include "agarios/GameConfig.h"
#include "agarios/QuadTree.h"
#include "agarios/gameObjects/Food.h"

class Window;

typedef std::unordered_map<std::string, sf::Vector2f> PlayersInput;
typedef std::unordered_map<std::string, Player*> Players;

class Game : public sf::Drawable
{

    private:
        static std::vector<std::string> names;

    public:
        GameConfig gameConfig;

    private:
        Players players;
        QuadTree foods;

    public:
        Game(GameConfig gameConfig);

    public:
        void update(PlayersInput playersInput);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void init();

        Player* join();
        void removeFood(Food* food);

        QuadTree getFoods() const;

        sf::Vector2f randomPosition() const;
        std::string randomName() const;

    private:
        void drawGrid(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif