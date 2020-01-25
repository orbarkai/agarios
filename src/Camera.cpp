#include "agarios/Camera.h"
#include "agarios/window.h"

Camera::Camera(Window* window, Player* target)
               : target(target)
               , window(window) { }

sf::View Camera::getView() {
    this->view.setSize(this->getScale());
    this->view.setCenter(this->getPosition());
    
    return this->view;
}

sf::Vector2f Camera::getPosition() const {
    if (this->target) return this->target->getPosition();
    return {0, 0};
}

sf::Vector2f Camera::getScale() const {
    sf::Vector2f scale(this->window->game->gameConfig.CAMERA_ZOOM * this->window->getSize().x,
                       this->window->game->gameConfig.CAMERA_ZOOM * this->window->getSize().y);

    return scale;
} 

void Camera::setTarget(Player* const target) {
    this->target = target;
}

Player* Camera::getTarget() const {
    return this->target;
}