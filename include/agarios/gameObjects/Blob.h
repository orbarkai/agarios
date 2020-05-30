#ifndef BLOB_H_
#define BLOB_H_

#include "SFML/System.hpp"
#include "SFGUI/Widgets.hpp"
#include "agarios/gameObjects/RigidBody.h"

class Window;
class Player;

class Blob : public RigidBody
{

    protected:
        Player* player;
        sf::Vector2f velocity;

        sfg::Table::Ptr guiTable;
        sfg::Button::Ptr nameLabel;
        sfg::Button::Ptr massLabel;

    public:
        Blob(Game* game,
             Player* player,
             std::string playerName,
             sf::Vector2f position, 
             sf::Color color);

    public:
        void update(sf::Vector2f inputVelocity, Window* window) ;
        float getSpeed() const;
        float getShrink() const;

    private:
        void applyBounds();

};

#endif