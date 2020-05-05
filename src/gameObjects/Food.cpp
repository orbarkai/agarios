#include "agarios/gameObjects/Food.h"
#include "services/Utils.h"
#include "services/Console.h"
#include "agarios/Game.h"

Food::Food(Game* game,
           sf::Vector2f position = sf::Vector2f(), 
           sf::Color color = sf::Color::Cyan) 
           : RigidBody(game, game->gameConfig.FOOD_MASS, position, color) { }

float Food::eat() {
    this->game->removeFood(this);
    return 1;
}