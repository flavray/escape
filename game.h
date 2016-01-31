#ifndef __GAME_H__
#define __GAME_H__

#include "laser.h"
#include "obstacle_manager.h"
#include "player.h"

#include <QGLWidget>
#include <QGLFunctions>

#include <ft2build.h>
#include FT_FREETYPE_H

class Game : public QGLWidget, public QGLFunctions {
Q_OBJECT

public:
    explicit Game(int framesPerSecond = 60, QWidget *parent = 0);

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent(QKeyEvent* keyEvent);
    void keyReleaseEvent(QKeyEvent* keyEvent);

    void reset();

    unsigned int score() { return _currentScore; }
    unsigned int maxScore() { return _maxScore; }
    unsigned int level() { return _level; }
    void updateScore(unsigned int s);

    Player player() { return _player; }
    Laser laser() { return _laser; }
    std::deque<Obstacle> obstacles() { return _obstacleManager.obstacles(); }
    FT_Face font() { return _font; }

    void setFont(FT_Face font);

    ~Game();

public slots:
    void timeoutSlot();

private:
    QTimer* t_Timer;

    unsigned int _currentScore;
    unsigned int _maxScore;
    unsigned int _level; /* A level is every tens of y() */
    FT_Face _font;

    Player _player;
    Laser _laser;
    ObstacleManager _obstacleManager;

    bool jumpPressed;

    void collisions();
};

#endif
