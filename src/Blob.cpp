#include "agarios/Blob.h"
#include "services/Utils.h"
#include "services/Console.h"

Blob::Blob(const GameConfig* gameConfig,
           sf::Vector2f position = sf::Vector2f(), 
           sf::Color color = sf::Color::Cyan) 
           : RigidBody(gameConfig, gameConfig->BLOB_INITIAL_MASS, position, color),
             velocity({0, 0}) { }

void Blob::update(sf::Vector2f inputVelocity) {

    // Velocity 
    Utils::Vectors::limit(inputVelocity, 1);
    sf::Vector2f velocityDelta = inputVelocity * this->getSpeed();
    this->velocity += velocityDelta;
    Utils::Vectors::limit(this->velocity, this->getSpeed());

    // Position
    this->setPosition(this->getPosition() + this->velocity);

}

float Blob::getSpeed() {
    return this->gameConfig->BLOB_SPEED_FACTOR / this->getMass();
}

float Blob::getShrink() {
    return this->getMass() * this->gameConfig->BLOB_SHRINK_FACTOR;
}