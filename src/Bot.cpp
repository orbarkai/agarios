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
    QuadTree allFoods = this->game->getFoods();
    sf::CircleShape searchRange = sf::CircleShape(std::max<float>(this->getBBox().width, this->getBBox().height));
    searchRange.setPosition(this->getPosition());

    std::vector<sf::Transformable*> objects = allFoods.getObjectsIntersects(searchRange);

    if (objects.size() == 0) {
        return Bot::Move();
    }

    sf::Transformable* closestObject = objects[0];
    sf::Vector2f thisPos = this->getPosition();

    for (int i = 1; i < objects.size(); i++) {
        sf::Vector2f foodPos = objects[i]->getPosition();
        sf::Vector2f closestFoodPos = closestObject->getPosition();
        if (Utils::Vectors::distance(thisPos, foodPos) < Utils::Vectors::distance(thisPos, closestFoodPos)) {
            closestObject = objects[i];
        }
    }

    sf::Vector2f inputVelocity = closestObject->getPosition() - thisPos;
    Utils::Vectors::normalize(inputVelocity);
    
    Bot::Move nextMove = {};
    nextMove.inputVelocity = inputVelocity;

    return nextMove;
}