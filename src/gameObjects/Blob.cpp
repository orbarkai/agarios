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
}

float Blob::getSpeed() const {
    return this->game->gameConfig.BLOB_SPEED_FACTOR / this->getMass();
}

float Blob::getShrink() const {
    return this->getMass() * this->game->gameConfig.BLOB_SHRINK_FACTOR;
}