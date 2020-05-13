#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>

#include "SFML/Graphics.hpp"
#include "agarios/GameObject.h"
#include "agarios/gameObjects/Blob.h"

class Game;

class Player : public sf::Drawable, public GameObject
{

    public:
        const std::string UUID;
        sf::Color color; 

    private:
        std::vector<std::shared_ptr<Blob>> blobs;
        std::string name;

    public:
        Player(Game* game, 
               sf::Vector2f position, 
               sf::Color color);

        virtual ~Player();

    public:
        void update(sf::Vector2f inputVelocity);
        sf::Vector2f getPosition() const;
        sf::FloatRect getBBox() const;
        sf::RectangleShape getBBoxShape() const;

        std::string getName() const;
        std::string getLoggerName() const;

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    public:
        bool operator==(Player& rhs);
};

#endif