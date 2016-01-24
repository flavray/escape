#include "obstacle.h"

Obstacle::Obstacle(float x, float y) : Obstacle(x, y, WIDTH, HEIGHT) { }

Obstacle::Obstacle(float x, float y, float w, float h) : _w(w), _h(h) {
    _x = x + w / 2.0f;
    _y = y + h / 2.0f;
}
