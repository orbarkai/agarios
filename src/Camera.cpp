#include "agarios/Camera.h"
#include "agarios/Game.h"
#include "services/Console.h"

Camera::Camera(Game* game, Player* target)
               : GameObject(game),
                 target(target) { }

sf::View Camera::getView() {
    sf::Transform transform;

    this->view.setSize(this->getScale());
    this->view.setCenter(this->getPosition());
    
    return this->view;
}

sf::Vector2f Camera::getPosition() const {
    if (this->target) return this->target->getPosition();
    return {0, 0};
}

sf::Vector2f Camera::getScale() const {
    sf::Vector2f scale(this->game->gameConfig.CAMERA_ZOOM * this->game->gameConfig.WINDOW_WIDTH,
                       this->game->gameConfig.CAMERA_ZOOM * this->game->gameConfig.WINDOW_HEIGHT);

    return scale;
} 

void Camera::setTarget(Player* target) {
    this->target = target;
}

Player* Camera::getTarget() const {
    return this->target;
}