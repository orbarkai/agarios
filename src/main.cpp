#include <iostream>
#include "SFML/Graphics.hpp"
#include "services/Console.h"
#include "services/Utils.h"
#include "agarios/Game.h"
#include "agarios/window.h"

int main()
{
    srand(time(0));

    Console::startSection(Console::paint("cyan", "Agarios"));

    GameConfig gameConfig = {};

    gameConfig.WINDOW_HEIGHT = 600;
    gameConfig.WINDOW_WIDTH = 800;
    gameConfig.CAMERA_ZOOM = 0.02;

    gameConfig.BLOB_INITIAL_MASS = 20;
    gameConfig.BLOB_SHRINK_FACTOR = 0.001;
    gameConfig.BLOB_SPEED_FACTOR = 1;

    gameConfig.VIRUS_COLOR = sf::Color::Green;

    Game game(gameConfig);

    Window window(&game, NULL);

    window.run();

    Console::endSection();

    return 0;
}