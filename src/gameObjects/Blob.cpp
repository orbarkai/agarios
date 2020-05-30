#include <math.h>
#include "agarios/gameObjects/Blob.h"
#include "services/Utils.h"
#include "services/Console.h"
#include "agarios/Game.h"
#include "SFGUI/SFGUI.hpp"

Blob::Blob(Game* game,
           Player* player,
           std::string playerName,
           sf::Vector2f position = sf::Vector2f(), 
           sf::Color color = sf::Color::Cyan) 
           : RigidBody(game, game->gameConfig.BLOB_INITIAL_MASS, position, color),
             player(player),
             velocity({0, 0}),
             guiTable(sfg::Table::Create()),
             nameLabel(sfg::Button::Create(playerName)),
             massLabel(sfg::Button::Create("mass")) {
        
    this->nameLabel->SetClass("bgLabel");
    this->massLabel->SetClass("bgLabel");

    this->guiTable->Attach(this->nameLabel, sf::Rect<sf::Uint32>( 0, 0, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0, 0) );
    this->guiTable->Attach(this->massLabel, sf::Rect<sf::Uint32>( 0, 1, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0, 0) );

    if (this->game->getWindow()) {
        this->game->getWindow()->desktop.Add(this->guiTable);
    }
}

void Blob::update(sf::Vector2f inputVelocity, Window* window) {
    // Velocity 
    Utils::Vectors::limit(inputVelocity, 1);
    sf::Vector2f velocityDelta = inputVelocity * this->getSpeed();
    this->velocity = velocityDelta;
    Utils::Vectors::limit(this->velocity, this->getSpeed());

    // Shrink
    this->addMass(-this->getShrink());

    // Position
    this->setPosition(this->getPosition() + this->velocity);

    // Bounds
    this->applyBounds();

    // Check food
    std::vector<sf::Transformable*> foods = this->game->getFoods().getObjectsIntersects(*this);
    for (int i = 0; i < foods.size(); i++) {
        Food* food = static_cast<Food*>(foods[i]);
        if (food && this->inEatRange(*food)) {
            this->addMass(food->eat());
        }
    }

    // If this blob will be draw in a specific window (client)
    // We need to update the gui table
    if (this->game->getWindow()) {
        this->massLabel->SetLabel(std::to_string(int(this->getMass())));
        sf::Vector2i topLeft = window->mapCoordsToPixel({this->getPosition().x - this->getRadius(), this->getPosition().y - this->getRadius()});
        sf::Vector2i topRight = window->mapCoordsToPixel({this->getPosition().x + this->getRadius(), this->getPosition().y + this->getRadius()});
        this->guiTable->SetAllocation({topLeft.x, topLeft.y, topRight.x - topLeft.x, topRight.y - topLeft.y});
        this->nameLabel->SetAllocation({10, (topRight.y - topLeft.y) / 2 - this->nameLabel->GetAllocation().height, this->nameLabel->GetAllocation().width - 20, this->nameLabel->GetAllocation().height});
        this->massLabel->SetAllocation({10, (topRight.y - topLeft.y) / 2, this->massLabel->GetAllocation().width - 20, this->massLabel->GetAllocation().height});
    }
}

float Blob::getSpeed() const {
    float speed = (1 / ((2 / this->game->gameConfig.BLOB_SPEED_MIN) + (this->game->gameConfig.BLOB_SPEED_FACTOR * this->getMass()))) + (this->game->gameConfig.BLOB_SPEED_MIN / 2);
    return speed;
}

float Blob::getShrink() const {
    return this->getMass() * this->game->gameConfig.BLOB_SHRINK_FACTOR;
}

void Blob::applyBounds() {
    sf::FloatRect thisBounds = this->getGlobalBounds();
    sf::FloatRect gameBounds = this->game->gameConfig.BOUNDS;
    if (thisBounds.left <= gameBounds.left) {
        this->setPosition(gameBounds.left + this->getRadius(), this->getPosition().y);
    } else if (thisBounds.left + thisBounds.width >= gameBounds.left + gameBounds.width) {
        this->setPosition(gameBounds.left + gameBounds.width - this->getRadius(), this->getPosition().y);
    }
    
    if (thisBounds.top <= gameBounds.top) {
        this->setPosition(this->getPosition().x, gameBounds.top + this->getRadius());
    } else if (thisBounds.top + thisBounds.height >= gameBounds.top + gameBounds.height) {
        this->setPosition(this->getPosition().x, gameBounds.top + gameBounds.height - this->getRadius());
    }
}