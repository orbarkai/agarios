
#include "agarios/Player.h"
#include "services/Utils.h"
#include "services/Console.h"
#include "agarios/GameObject.h"

Player::Player(Game* game,
               sf::Vector2f position,
               sf::Color color = sf::Color::Cyan) 
               : GameObject(game),
                 UUID(Utils::UUID()),
                 blobs({std::make_shared<Blob>(game, position, color)}) { }

sf::Vector2f Player::getPosition() {
    if (this->blobs.size() == 0) return {0, 0};

    sf::Vector2f position = {0, 0};

    for (int i = 0; i < this->blobs.size(); i++) {
        position += this->blobs[i]->getCenter();
    }

    position /= (float)this->blobs.size();

    return position;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int i = 0; i < this->blobs.size(); i++) {
        target.draw(*this->blobs[i], states);
    }
}

void Player::update(sf::Vector2f inputVelocity) {
    for (int i = 0; i < this->blobs.size(); i++) {
        this->blobs[i]->update(inputVelocity);
    }
}

bool Player::operator==(Player& rhs) {
    return this->UUID == rhs.UUID;
}