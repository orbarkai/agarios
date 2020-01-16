#include "cmath"
#include "agarios/RigidBody.h"

RigidBody::RigidBody(const Game* game,
                     float mass, 
                     sf::Vector2f position = sf::Vector2f(), 
                     sf::Color color = sf::Color::Cyan) 
                     : mass(mass), 
                     sf::CircleShape(this->getRadius()),
                     GameObject(game) {

    this->setFillColor(color);
    this->setPosition(position);
    this->setRadius(this->getRadius());

}


void RigidBody::addMass(float modifier) {
    this->mass += modifier;
    this->mass = std::min<float>(this->mass, 0);
}

float RigidBody::getMass() {
    return this->mass;
};

float RigidBody::getRadius() {
    return std::sqrt(this->mass / M_PI);
};

sf::Vector2f RigidBody::getCenter() {
    return this->getPosition() + sf::Vector2f(this->getRadius(), this->getRadius());
}