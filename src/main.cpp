#include <iostream>
#include "SFML/Graphics.hpp"
#include "services/Console.h"
#include "services/Utils.h"
#include "services/FS.h"
#include "agarios/Game.h"
#include "agarios/window.h"

int main()
{
    srand(time(0));

    Console::endSection();
    Console::startSection(Console::paint("cyan", "Agarios"));
    Console::endSection();
    Console::log();

    GameConfig gameConfig = {};
    gameConfig.GAME_MODE = GameConfig::GameMode::DEV;
    Game game(gameConfig);
    Window window(&game, NULL);

    window.run();

    return 0;
}