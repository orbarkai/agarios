#include "agarios/Bot.h"
#include "agarios/Game.h"
#include "services/Utils.h"


Bot::Bot(Game* game, 
        sf::Vector2f position, 
        sf::Color color)
        : Player(game, position, color) { }

Bot::Move Bot::getNextMove() {
    // For now a simple bot that goes to the nearest food
    // In the future the bot will use a neural network
    std::vector<Food*> foods = this->game->getFoods();

    if (foods.size() == 0) {
        return Bot::Move();
    }

    Food* closestFood = foods[0];
    sf::Vector2f thisPos = this->getPosition();

    for (int i = 1; i < foods.size(); i++) {
        sf::Vector2f foodPos = foods[i]->getPosition();
        sf::Vector2f closestFoodPos = closestFood->getPosition();
        if (Utils::Vectors::distance(thisPos, foodPos) < Utils::Vectors::distance(thisPos, closestFoodPos)) {
            closestFood = foods[i];
        }
    }

    sf::Vector2f inputVelocity = closestFood->getPosition() - thisPos;
    Utils::Vectors::normalize(inputVelocity);
    
    Bot::Move nextMove = {};
    nextMove.inputVelocity = inputVelocity;

    return nextMove;
}