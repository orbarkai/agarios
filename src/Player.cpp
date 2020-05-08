
#include "agarios/Player.h"
#include "services/Utils.h"
#include "services/Console.h"
#include "agarios/GameObject.h"
#include "agarios/gameObjects/Blob.h"

Player::Player(Game* game,
               sf::Vector2f position,
               sf::Color color = sf::Color::Cyan) 
               : GameObject(game),
                 UUID(Utils::UUID()),
                 blobs({std::make_shared<Blob>(game, position, color)}) { }

Player::~Player() { }
                 
sf::Vector2f Player::getPosition() const {
    if (this->blobs.size() == 0) return {0, 0};

    sf::Vector2f position = {0, 0};

    for (int i = 0; i < this->blobs.size(); i++) {
        position += this->blobs[i]->getPosition();
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

sf::FloatRect Player::getBBox() const {
    float minX, maxX, minY, maxY;

    for (int i = 0; i < this->blobs.size(); i++) {
        float radius = this->blobs[i]->getRadius();
        sf::Vector2f center = this->blobs[i]->getPosition();

        if (i == 0) {
            minX = center.x - radius;
            maxX = center.x + radius;
            minY = center.y - radius;
            maxY = center.y + radius;
        } else {
            minX = std::min<float>(minX, center.x - radius);
            maxX = std::max<float>(maxX, center.x + radius);
            minY = std::min<float>(minY, center.y - radius);
            maxY = std::max<float>(maxY, center.y + radius);
        }
    }
    
    return sf::FloatRect(minX, minY, (maxX - minX), (maxY - minY));
}

sf::RectangleShape Player::getBBoxShape() const {
    sf::FloatRect bBox = this->getBBox();
    sf::RectangleShape bBoxShape({bBox.width, bBox.height});
    
    bBoxShape.setPosition({bBox.left, bBox.top});
    bBoxShape.setOutlineColor(sf::Color::Red);
    bBoxShape.setOutlineThickness(0.1);
    bBoxShape.setFillColor(sf::Color::Transparent);

    return bBoxShape;
}

bool Player::operator==(Player& rhs) {
    return this->UUID == rhs.UUID;
}