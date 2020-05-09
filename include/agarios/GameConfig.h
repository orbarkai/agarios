#ifndef GAME_CONFIG_H_
#define GAME_CONFIG_H_

#include "SFML/Graphics.hpp"

struct GameConfig 
{

    enum class GameMode {DEV, PRODUCTION, GOD};
    enum class GridMode {SYMETRIC, QUADTREE};

    GameMode GAME_MODE;
    GridMode GRID_MODE;

    unsigned int WINDOW_WIDTH;
    unsigned int WINDOW_HEIGHT;

    sf::Rect<float> BOUNDS;

    float CAMERA_ZOOM;
    float GRID_MARGIN;

    sf::Color VIRUS_COLOR;

    float BLOB_SPEED_FACTOR;
    float BLOB_SPEED_MIN;
    float BLOB_INITIAL_MASS;
    float BLOB_SHRINK_FACTOR;

    float FOOD_MASS;
    float FOOD_PER_PIXEL;

    GameConfig() 
    : GAME_MODE(GameMode::PRODUCTION)
    , GRID_MODE(GridMode::QUADTREE)
    , BOUNDS(sf::Rect<float>({0, 0}, {200, 200}))
    , WINDOW_WIDTH(1280)
    , WINDOW_HEIGHT(720)
    , CAMERA_ZOOM(4)
    , GRID_MARGIN(2.5)
    , BLOB_INITIAL_MASS(20)
    , BLOB_SPEED_MIN(0.2)
    , BLOB_SPEED_FACTOR(0.1)
    , BLOB_SHRINK_FACTOR(0.0005)
    , VIRUS_COLOR(sf::Color::Green)
    , FOOD_MASS(0.5)
    , FOOD_PER_PIXEL(0.05) { }
};

#endif