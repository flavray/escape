#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

class Obstacle {
public:
    Obstacle(float x, float y);
    Obstacle(float x, float y, float w, float h);

    float x() { return _x; }
    float y() { return _y; }
    float w() { return _w; }
    float h() { return _h; }

    static constexpr const float WIDTH = 0.05f;
    static constexpr const float HEIGHT = 0.2f;

private:
    float _x, _y;
    float _w, _h;
};

#endif
