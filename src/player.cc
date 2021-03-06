#include "player.h"

#include "scene.h"

#include <iostream>
#include <QtOpenGL>

// Player horizontal speed
#define SPEED_X 0.05

// Player vertical speed
#define INITIAL_SPEED 0.04
#define SPEED_LOWER 0.003

Player::Player() {
    _x = -0.45f;
    _y = 0.0f;

    _w = 0.1f;
    _h = 0.05f;

    _jumping = false;
    _direction = RIGHT;
}

void Player::jump() {
    _jumping = true;
    _speedY = INITIAL_SPEED;
}

void Player::update(bool& jumpPressed) {
    if (_jumping) {
        _speedY -= SPEED_LOWER;

        _y += _speedY;

        if (_direction == RIGHT)
            _x += SPEED_X;
        else
            _x -= SPEED_X;

        // Collision
        if ((_x - _w / 2.0f <= LEFT_SIDE) || (_x + _w / 2.0f >= RIGHT_SIDE)) {
            afterJump();
            jumpPressed = false; /* to avoid autojump */
        }
    } else {
        if (_y > 0.0f)
            _y -= 0.005;
    }
}

bool Player::collision(Obstacle obstacle) {
    float px = _x - _w / 2.0f;
    float py = _y + _h / 2.0f;

    float ox = obstacle.x() - obstacle.w() / 2.0f;
    float oy = obstacle.y() + obstacle.h() / 2.0f;

    // player is not on a side
    if ((px != ox + obstacle.w()) && (px + _w != ox))
        return false;

    return ((py > oy - obstacle.h()) && (py < oy)) || ((py > oy) && (py - _h < oy));
}

// Adjust player's position to stick to the sides
void Player::afterJump() {
    _jumping = false;

    if (_direction == LEFT)
        _x = LEFT_SIDE + _w / 2.0f;
    else
        _x = RIGHT_SIDE - _w / 2.0f;

    _direction = _direction == LEFT ? RIGHT : LEFT;
}
