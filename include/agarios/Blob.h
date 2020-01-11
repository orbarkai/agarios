#ifndef BLOB_H_
#define BLOB_H_

#include "SFML/System.hpp"
#include "agarios/RigidBody.h"

class Blob : public RigidBody
{

    protected:
        sf::Vector2f velocity;

    public:
        Blob(const GameConfig* gameConfig,
             sf::Vector2f position, 
             sf::Color color);

    public:
        void update(sf::Vector2f inputVelocity);
        float getSpeed();
        float getShrink();

};

#endif