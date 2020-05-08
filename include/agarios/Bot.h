#ifndef BOT_H_
#define BOT_H_


#include "SFML/Graphics.hpp"
#include "agarios/Player.h"

class Bot : public Player
{

    public:
        // A move decision for one frame
        class Move 
        {

            public:
                sf::Vector2f inputVelocity;

        };

    public:
        Bot(Game* game, 
            sf::Vector2f position, 
            sf::Color color);

    public:
        // Get the move decision for the next frame
        Move getNextMove();

};

#endif