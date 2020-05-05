#ifndef FOOD_H_
#define FOOD_H_

#include "SFML/System.hpp"
#include "agarios/gameObjects/RigidBody.h"

class Food : public RigidBody
{

    public:
        Food(Game* game,
             sf::Vector2f position, 
             sf::Color color);

    public:
        // removes the food from the game and returns the mass that should be added
        float eat();

};

#endif