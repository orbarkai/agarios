#ifndef CAMERA_H_
#define CAMERA_H_


#include "SFML/Graphics.hpp"

class Window;
class Player;

class Camera
{

    private:
        Window* window;
        Player* target;
        sf::View view;

    public:
        Camera(Window* window, Player* target);

    public:
        sf::View getView();

        void setTarget(Player* const target);
        Player* getTarget() const;

    private:
        sf::Vector2f getScale() const;
        sf::Vector2f getPosition() const;

};

#endif