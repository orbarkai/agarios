#include <iostream>
#include "SFML/Graphics.hpp"
#include "services/Console.h"
#include "services/Utils.h"
#include "agarios/Player.h"

int main()
{
    srand(time(0));

    Console::startSection(Console::paint("cyan", "Agarios"));

    GameConfig gameConfig = {};

    gameConfig.BLOB_INITIAL_MASS = 20;
    gameConfig.BLOB_SHRINK_FACTOR = 0.001;
    gameConfig.BLOB_SPEED_FACTOR = 4;
    gameConfig.VIRUS_COLOR = sf::Color::Green;

    Player p(&gameConfig, {100, 100}, sf::Color::Cyan);

    // Declare and create a new render-window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
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
        }
        // Clear the whole window before rendering a new frame
        window.clear();
        // Draw some graphical entities
        window.draw(p);

        // End the current frame and display its contents on screen
        window.display();
    }

    Console::endSection();

    return 0;
}