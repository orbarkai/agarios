#ifndef RIGID_BODY_H_
#define RIGID_BODY_H_

#include "SFML/Graphics.hpp"
#include "agarios/GameObject.h"

class RigidBody : public sf::CircleShape, public GameObject
{
    private:
        float mass;

    public:
        RigidBody(Game* game,
                  float mass, 
                  sf::Vector2f position, 
                  sf::Color color);

    public:
        virtual void addMass(const float modifier);
        virtual void setMass(const float mass);
        void updateOrigin();
        float getMass() const;
        float getRadius() const;

        bool inEatRange(RigidBody const other);
};

#endif