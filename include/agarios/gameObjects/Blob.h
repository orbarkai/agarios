#ifndef BLOB_H_
#define BLOB_H_

#include "SFML/System.hpp"
#include "agarios/gameObjects/RigidBody.h"

class Blob : public RigidBody
{

    protected:
        sf::Vector2f velocity;

    public:
        Blob(Game* game,
             sf::Vector2f position, 
             sf::Color color);

    public:
        void update(sf::Vector2f inputVelocity) ;
        float getSpeed() const;
        float getShrink() const;

};

#endif