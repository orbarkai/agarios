#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

class Game;

class GameObject
{

    protected:
        Game* game;

    public:
        GameObject(Game* game);

};

#endif