#include "agarios/Player.h"
#include "services/Utils.h"

Player::Player(GameConfig* gameConfig,
               sf::Vector2f position,
               sf::Color color = sf::Color::Cyan) 
               : GameObject(gameConfig),
                 UUID(Utils::UUID()),
                 blobs({Blob(gameConfig, position, color)}) { }

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int i = 0; i < this->blobs.size(); i++) {
        target.draw(this->blobs[i], states);
    }
}