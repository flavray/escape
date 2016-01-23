#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player {
public:
    Player();
    void jump();

    void update();

    float x() { return _x; }
    float y() { return _y; }
    float w() { return _w; }
    float h() { return _h; }
    bool jumping() { return _jumping; }

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
