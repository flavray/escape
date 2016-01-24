#include "obstacle_manager.h"

#include "scene.h"

ObstacleManager::ObstacleManager()
    : _distribution(0.6f, 0.4f)
{
    // generate first obstacle - chosen on fair dice roll
    _obstacles.push_back(Obstacle(RIGHT_SIDE, 1.0f));
    _lastDirection = Player::RIGHT;

    for (int i = 1; i < N_OBSTACLES; i++)
        generateObstacle();
}

void ObstacleManager::update(float y) {
    // out of screen
    while (y - _obstacles.front().y() > 1.0f) {
        _obstacles.pop_front();
        generateObstacle();
    }
}

void ObstacleManager::generateObstacle() {
    float lastY = _obstacles.back().y();

    // change side
    float x;
    if (_lastDirection == Player::LEFT) {
        x = RIGHT_SIDE;
        _lastDirection = Player::RIGHT;
    } else {
        x = LEFT_SIDE - Obstacle::WIDTH;
        _lastDirection = Player::LEFT;
    }

    float y = lastY + _distribution(_generator);

    _obstacles.push_back(Obstacle(x, y));
}
