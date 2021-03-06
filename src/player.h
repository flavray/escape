#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "obstacle.h"

class Player {
public:
    Player();
    void jump();

    void update(bool& jumpPressed);

    float x() { return _x; }
    float y() { return _y; }
    float w() { return _w; }
    float h() { return _h; }
    bool jumping() { return _jumping; }

    bool collision(Obstacle obstacle);

    enum Direction { LEFT, RIGHT };

private:
    float _x, _y;
    float _w, _h;
    bool _jumping;
    Direction _direction;

    float _speedY;

    void afterJump();
};

#endif
