#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

class Game;

class GameObject
{

    protected:
        const Game* game;

    public:
        GameObject(const Game* game);

};

#endif