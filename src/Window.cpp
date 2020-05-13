#include "agarios/window.h"
#include "services/Console.h"
#include "services/Utils.h"


Window::Window(Game* game, Player* mainPlayer=NULL)
               : sf::RenderWindow({game->gameConfig.WINDOW_WIDTH,
                                   game->gameConfig.WINDOW_HEIGHT},
                                   "Agarios")
               , GameObject(game)
               , camera(this, NULL)
               , sfgui()
               , desktop()
               , clock()
               , fpsLabel(sfg::Label::Create("")) {

    this->setGame(game);
    this->setMainPlayer(mainPlayer);

    if (this->game && !this->mainPlayer) {
        this->setMainPlayer(this->game->join());
    }

    this->desktop.Add(this->fpsLabel);
}

void Window::run() {
    // Set framerate
    this->setFramerateLimit(60);

	// reset OpenGL states. Otherwise we wouldn't see anything.
	this->resetGLStates();

    while (this->isOpen())
    {
        //FPS
        float elapsedTime = this->clock.restart().asSeconds();
        float fps = 1 / elapsedTime;
        // Event to pull
        sf::Event event;
        while (this->pollEvent(event))
        {
            // Handle GUI events (click, hover, drag etc...)
            this->desktop.HandleEvent( event );

            // Request for closing the window
            if (event.type == sf::Event::Closed) {
                this->close();
            }
                
             // Zoom
            if (event.type == sf::Event::MouseWheelMoved) {
                if (this->game->gameConfig.GAME_MODE == GameConfig::GameMode::DEV || this->game->gameConfig.GAME_MODE == GameConfig::GameMode::GOD) {
                    float delta = event.mouseWheel.delta;
                    this->camera.setZoom(this->camera.getZoom() - delta);
                }
            }
        }

        // Clear window
        this->clear();

         // Set drawing view
        this->setView(this->camera.getView());

        // Update SFGUI with elapsed seconds since last call.
		this->desktop.Update(elapsedTime);

        // Update fps text
        this->fpsLabel->SetText("fps: " + std::to_string(fps));

        // Update game
        this->game->update({{this->mainPlayer->UUID, this->getPlayerInput()}});

        // Draw game
        this->draw(*this->game);

        // Draw GUI
        this->sfgui.Display( *this );

        // Flip buffers
        this->display();
    }
}

void Window::setGame(Game* const game) {
    this->game = game;
}

Game* Window::getGame() const {
    return this->game;
}

Player* Window::getMainPlayer() const {
    return this->mainPlayer;
}

void Window::setMainPlayer(Player* const player) {
    this->mainPlayer = player;
    if (this->mainPlayer) {
        this->camera.setTarget(this->mainPlayer);
    }
}

sf::Vector2f Window::getPlayerInput() {
    sf::Vector2f center = {(float)this->getSize().x / (float)2.0, (float)this->getSize().y / (float)2.0};
    sf::Vector2i mouse = sf::Mouse::getPosition(*this);

    sf::Vector2f input = {(float)mouse.x - (float)center.x, (float)mouse.y - (float)center.y};
    float maxRadius = (float)std::min<unsigned int>(this->getSize().x, this->getSize().y) * 0.3;

    Utils::Vectors::limit(input, maxRadius);
    input /= maxRadius;
    
    return input;
}