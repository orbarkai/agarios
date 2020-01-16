#ifndef CAMERA_H_
#define CAMERA_H_


#include "SFML/Graphics.hpp"
#include "agarios/GameObject.h"

class Player;

class Camera : public GameObject
{

    private:
        Player* target;
        sf::View view;

    public:
        Camera(Game* game, Player* target);

    public:
        sf::View getView();

        void setTarget(Player* target);
        Player* getTarget() const;

    private:
        sf::Vector2f getScale() const;
        sf::Vector2f getPosition() const;

};

#endif