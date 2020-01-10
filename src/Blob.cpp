#include "agarios/Blob.h"
#include "services/Utils.h"
#include "services/Console.h"

Blob::Blob(const GameConfig* gameConfig,
           float mass, 
           sf::Vector2f position = sf::Vector2f(), 
           sf::Color color = sf::Color::Cyan) 
           : RigidBody(gameConfig, mass, position, color) { }

sf::Vector2f Blob::getVelocity(sf::Vector2f inputVelocity) {
    Utils::Vectors::limit(inputVelocity, 1);
    return inputVelocity * this->getSpeed();
}

float Blob::getSpeed() {
    return this->getMass() * this->gameConfig->BLOB_SPEED_FACTOR;
}

float Blob::getShrink() {
    return this->getMass() * this->gameConfig->BLOB_SHRINK_FACTOR;
}