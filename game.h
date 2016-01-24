#ifndef __GAME_H__
#define __GAME_H__

#include "laser.h"
#include "obstacle_manager.h"
#include "player.h"

#include <QGLWidget>

class Game : public QGLWidget {
Q_OBJECT

public:
    explicit Game(int framesPerSecond = 60, QWidget *parent = 0);

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent(QKeyEvent* keyEvent);
    void keyReleaseEvent(QKeyEvent* keyEvent);

    Player player() { return _player; }
    Laser laser() { return _laser; }
    std::deque<Obstacle> obstacles() { return _obstacleManager.obstacles(); }

public slots:
    void timeoutSlot();

private:
    QTimer* t_Timer;

    Player _player;
    Laser _laser;
    ObstacleManager _obstacleManager;

    bool jumpPressed;
};

#endif
