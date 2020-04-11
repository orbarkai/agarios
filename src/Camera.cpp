#include "agarios/Camera.h"
#include "agarios/window.h"
#include "services/Console.h"
#include "services/Utils.h"

Camera::Camera(Window* window, Player* target)
               : target(target)
               , window(window)
               , zoom(window->game->gameConfig.CAMERA_ZOOM) { }

sf::View Camera::getView() {

    sf::FloatRect bBox = this->target->getBBox();
    bBox.width = bBox.width * ((float)this->window->getSize().x / (float)this->window->getSize().y);
    this->view.reset(bBox);
    this->view.setCenter(this->target->getPosition());
    this->view.zoom(this->zoom);
    
    return this->view;
}

void Camera::setTarget(Player* const target) {
    this->target = target;
}

Player* Camera::getTarget() const {
    return this->target;
}

void Camera::setZoom(float const zoom) {
    this->zoom = zoom;
}

float Camera::getZoom() const {
    return this->zoom;
}