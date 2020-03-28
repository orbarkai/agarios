#ifndef GAME_CONFIG_H_
#define GAME_CONFIG_H_

#include "SFML/Graphics.hpp"

struct GameConfig 
{

    unsigned int WINDOW_WIDTH;
    unsigned int WINDOW_HEIGHT;

    float CAMERA_ZOOM;
    float GRID_MARGIN;

    sf::Color VIRUS_COLOR;

    float BLOB_INITIAL_MASS;
    float BLOB_SPEED_FACTOR;
    float BLOB_SHRINK_FACTOR;

    GameConfig() 
    : WINDOW_WIDTH(1280)
    , WINDOW_HEIGHT(720)
    , CAMERA_ZOOM(4)
    , GRID_MARGIN(1.5)
    , BLOB_INITIAL_MASS(20)
    , BLOB_SHRINK_FACTOR(0.0005)
    , BLOB_SPEED_FACTOR(1.7)
    , VIRUS_COLOR(sf::Color::Green) { }
};

#endif