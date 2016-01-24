#include "laser.h"

Laser::Laser() : _y(-0.2f) { }

void Laser::update() {
    _y += SPEED;
}
