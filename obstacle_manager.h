#ifndef __OBSTACLE_MANAGER_H__
#define __OBSTACLE_MANAGER_H__

#include "obstacle.h"
#include "player.h"

#include <deque>
#include <random>

class ObstacleManager {
public:
    ObstacleManager();
    void update(float y);

    std::deque<Obstacle> obstacles() { return _obstacles; }

    static constexpr const int N_OBSTACLES = 10;

private:
    std::deque<Obstacle> _obstacles;

    Player::Direction _lastDirection;

    std::default_random_engine _generator;
    std::normal_distribution<float> _distribution;

    void generateObstacle();
};

#endif
