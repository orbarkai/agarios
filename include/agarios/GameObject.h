#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "agarios/GameConfig.h"

class GameObject
{

    protected:
        const GameConfig* gameConfig;

    public:
        GameObject(const GameConfig* gameConfig);

};

#endif