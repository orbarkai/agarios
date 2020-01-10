#ifndef RIGID_BODY_H_
#define RIGID_BODY_H_

#include "SFML/Graphics.hpp"
#include "agarios/GameObject.h"

class RigidBody : public sf::CircleShape, public GameObject
{
    private:
        float mass;

    public:
        RigidBody(const GameConfig* gameConfig,
                  float mass, 
                  sf::Vector2f position, 
                  sf::Color color);

    public:
        virtual void addMass(float modifier);
        float getMass();
        float getRadius();
};

#endif