#include "cmath"
#include "agarios/gameObjects/RigidBody.h"

RigidBody::RigidBody(Game* game,
                     float mass, 
                     sf::Vector2f position = sf::Vector2f(), 
                     sf::Color color = sf::Color::Cyan) 
                     : mass(mass), 
                     sf::CircleShape(this->getRadius()),
                     GameObject(game) {

    this->setFillColor(color);
    this->setPosition(position);
    this->setRadius(this->getRadius());
    this->updateOrigin();
}


void RigidBody::addMass(const float modifier) {
    this->setMass(this->mass + modifier);
}

void RigidBody::setMass(const float mass) {
    this->mass = std::max<float>(mass, 0);
    this->updateOrigin();
}

void RigidBody::updateOrigin() {
    this->setRadius(this->getRadius());
    this->setOrigin(this->getRadius(), this->getRadius());
}

float RigidBody::getMass() const {
    return this->mass;
};

float RigidBody::getRadius() const {
    return std::sqrt(this->mass / M_PI);
};