#ifndef __SCENE_H__
#define __SCENE_H__

#include <QtOpenGL>

#include "game.h"

// Field limits
#define LEFT_SIDE  -0.5f
#define RIGHT_SIDE 0.5f

/* OpenGL drawing backend */
class Scene {
public:
    static void draw(Game* game);

private:
    static Image* _digitsImage;
};

#endif
