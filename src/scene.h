#ifndef __SCENE_H__
#define __SCENE_H__

#include "game.h"

// Field limits
#define LEFT_SIDE  -0.5f
#define RIGHT_SIDE 0.5f

class Scene {
public:
    static void draw(Game* game);
};

#endif
