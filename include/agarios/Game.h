#include "agarios/Player.h"

class Game : public GameObject, public sf::Drawable
{

    private:
        std::vector<Player> players;
        Player* mainPlayer;

    public:
        Game(GameConfig* gameConfig, bool initiateMainPlayer);

    public:
        void update(sf::Vector2f inputVelocity);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        Player* getMainPlayer();
        void setMainPlayer(Player player);

};