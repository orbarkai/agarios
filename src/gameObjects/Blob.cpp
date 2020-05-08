#include "agarios/gameObjects/Blob.h"
#include "services/Utils.h"
#include "services/Console.h"
#include "agarios/Game.h"

Blob::Blob(Game* game,
           sf::Vector2f position = sf::Vector2f(), 
           sf::Color color = sf::Color::Cyan) 
           : RigidBody(game, game->gameConfig.BLOB_INITIAL_MASS, position, color),
             velocity({0, 0}) { }

void Blob::update(sf::Vector2f inputVelocity) {

    // Velocity 
    Utils::Vectors::limit(inputVelocity, 1);
    sf::Vector2f velocityDelta = inputVelocity * this->getSpeed();
    this->velocity = velocityDelta;
    Utils::Vectors::limit(this->velocity, this->getSpeed());

    // Shrink
    this->addMass(-this->getShrink());

    // Position
    this->setPosition(this->getPosition() + this->velocity);

    // Bounds
    this->applyBounds();

    // Check food
    std::vector<Food*> foods = this->game->getFoods();
    for (int i = 0; i < foods.size(); i++) {
        if (this->inEatRange(*foods[i])) {
            this->addMass(foods[i]->eat());
        }
    }
}

float Blob::getSpeed() const {
    float speed = (1 / ((2 / this->game->gameConfig.BLOB_SPEED_MIN) + (this->game->gameConfig.BLOB_SPEED_FACTOR * this->getMass()))) + (this->game->gameConfig.BLOB_SPEED_MIN / 2);
    return speed;
}

float Blob::getShrink() const {
    return this->getMass() * this->game->gameConfig.BLOB_SHRINK_FACTOR;
}

void Blob::applyBounds() {
    sf::FloatRect thisBounds = this->getGlobalBounds();
    if (thisBounds.left <= 0) {
        this->setPosition(this->getRadius(), this->getPosition().y);
    } else if (thisBounds.left + thisBounds.width >= this->game->gameConfig.BOUNDS.x) {
        this->setPosition(this->game->gameConfig.BOUNDS.x - this->getRadius(), this->getPosition().y);
    }
    
    if (thisBounds.top <= 0) {
        this->setPosition(this->getPosition().x, this->getRadius());
    } else if (thisBounds.top + thisBounds.height >= this->game->gameConfig.BOUNDS.y) {
        this->setPosition(this->getPosition().x, this->game->gameConfig.BOUNDS.y - this->getRadius());
    }
}