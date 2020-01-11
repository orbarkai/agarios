#include "agarios/Blob.h"

class Player : public GameObject, public sf::Drawable
{

    public:
        const std::string UUID;
        sf::Color color; 

    private:
        std::vector<Blob> blobs;

    public:
        Player(GameConfig* gameConfig, 
               sf::Vector2f position, 
               sf::Color color);

    public:
        void update(sf::Vector2f inputVelocity);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
