#ifndef GAME_CONFIG_H_
#define GAME_CONFIG_H_

#include "SFML/Graphics.hpp"

struct GameConfig 
{

    float WINDOW_WIDTH;
    float WINDOW_HEIGHT;

    float CAMERA_ZOOM;

    sf::Color VIRUS_COLOR;

    float BLOB_INITIAL_MASS;
    float BLOB_SPEED_FACTOR;
    float BLOB_SHRINK_FACTOR;

};

#endif