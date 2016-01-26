#include "laser.h"

Laser::Laser() : _y(-0.2f) { }

void Laser::update(float y) {
    if (y > 0.5f)
        _y += SPEED;

    // always keep the laser close
    if (y - _y > 1.0f)
        _y = y - 1.0f;
}
