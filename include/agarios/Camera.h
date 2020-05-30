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
        float zoom;

    public:
        Camera() = default;
        Camera(Window* window, Player* target);

    public:
        sf::View getView();

        void setTarget(Player* const target);
        Player* getTarget() const;

        void setZoom(float const zoom);
        float getZoom() const;

};

#endif