#ifndef GAME_H_
#define GAME_H_

#include <unordered_map>
#include "agarios/Player.h"
#include "agarios/GameConfig.h"
#include "agarios/QuadTree.h"
#include "agarios/gameObjects/Food.h"
#include "agarios/window.h"

typedef std::unordered_map<std::string, sf::Vector2f> PlayersInput;
typedef std::unordered_map<std::string, Player*> Players;

class Game : public sf::Drawable
{

    private:
        static std::vector<std::string> names;

    public:
        GameConfig gameConfig;

    private:
        // If the game is redered in the client side, it has a window.
        // Else, this would be NULL.
        Window* window;

        // Game stuff
        Players players;
        QuadTree foods;

    public:
        Game(GameConfig gameConfig, Window* window);

    public:
        void update(PlayersInput playersInput, Window* window);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void init();

        Player* join();
        void removeFood(Food* food);

        QuadTree getFoods() const;
        Window* getWindow() const;
        void setWindow(Window* const window);

        sf::Vector2f randomPosition() const;
        std::string randomName() const;

    private:
        void drawGrid(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif