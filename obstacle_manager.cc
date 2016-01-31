#include <cmath>
#include <chrono>

#include "obstacle_manager.h"

#include "scene.h"

ObstacleManager::ObstacleManager()
    : _space_distribution(0.6f, 0.4f)
    , _size_distribution(Obstacle::HEIGHT, 0.1f)
{
    /* Init randgen */
    time_t tm = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    _generator.seed(tm);

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

    float y = lastY + _space_distribution(_generator);
    float h = _size_distribution(_generator);

    _obstacles.push_back(Obstacle(x, y, Obstacle::WIDTH, h));
}

/* This is used to vary the "randomness" of the obstacles flow, in
   order to make the game harder and harder.
*/
void ObstacleManager::updateObstacleLevel(float y) {
    float coef = log10(y);

    /* Every 100 meters, the gaussian is recentered lower. */
    _space_distribution = std::normal_distribution<float>(0.6f - 0.1 * coef, 0.1f);

    /* Every 100 meters*/
    _size_distribution = std::normal_distribution<float>(Obstacle::HEIGHT, 0.1f + 0.1f * coef);
}
