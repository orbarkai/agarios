#include <iostream>
#include "SFML/Graphics.hpp"
#include "services/Console.h"
#include "services/Utils.h"
#include "agarios/Game.h"

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

    Game game(gameConfig, true);

    // Declare and create a new render-window
    sf::RenderWindow window(sf::VideoMode(gameConfig.WINDOW_WIDTH, gameConfig.WINDOW_HEIGHT), "SFML window");
    // Limit the framerate to 60 frames per second (this step is optional)
    window.setFramerateLimit(60);
    // The main loop - ends as soon as the window is closed
    while (window.isOpen())
    {
        // Event processing
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Request for closing the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                game.gameConfig.WINDOW_WIDTH  = event.size.width;
                game.gameConfig.WINDOW_HEIGHT = event.size.height;
            }
        }
        // Clear the whole window before rendering a new frame
        window.clear();

        window.setView(game.camera.getView());

        game.update({1, 0});
        // Draw some graphical entities
        window.draw(game);
        // End the current frame and display its contents on screen
        window.display();
    }

    Console::endSection();

    return 0;
}