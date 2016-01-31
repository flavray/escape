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
    void updateObstacleLevel(unsigned int level);

    std::deque<Obstacle> obstacles() { return _obstacles; }

    static constexpr const int N_OBSTACLES = 10;

private:
    std::deque<Obstacle> _obstacles;

    Player::Direction _lastDirection;

    std::knuth_b _generator;
    std::normal_distribution<float> _space_distribution;
    std::normal_distribution<float> _size_distribution;

    void generateObstacle();
};

#endif
