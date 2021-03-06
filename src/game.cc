#include "game.h"

#include "scene.h"

#include <QtOpenGL>
#include <iostream>

Game::Game(int framesPerSecond, QWidget *parent)
    : QGLWidget(parent)
{
    setWindowTitle(QString("escape"));

    t_Timer = new QTimer(this);
    t_Timer->start(1000 / framesPerSecond);

    connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeoutSlot()));

    _currentScore = 0;
    _maxScore = 0;
    _level = 0;

    jumpPressed = false;
}

void Game::reset() {
    /* Reset score and level */
    updateScore(0);
    _level = 0;

    /* Reset player position */
    _player = Player();

    /* Reset world */
    _laser = Laser();
    _obstacleManager = ObstacleManager();

    /* Reset misc state */
    jumpPressed = false;
}

void Game::keyPressEvent(QKeyEvent* keyEvent) {
    if (keyEvent->isAutoRepeat())
        return;

    switch (keyEvent->key()) {
    case Qt::Key_Escape:
        close();
        break;

    case Qt::Key_Space:
        jumpPressed = true;
        break;

    case Qt::Key_R:
        glRotatef(90, 0, 0, 1);
        break;
    }
}

void Game::keyReleaseEvent(QKeyEvent* keyEvent) {
    switch (keyEvent->key()) {
    case Qt::Key_Space:
        jumpPressed = false;
        break;
    }
}

void Game::mousePressEvent(QMouseEvent* mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton)
        jumpPressed = true;
    else if (mouseEvent->button() == Qt::RightButton)
        glRotatef(90, 0, 0, 1);
}

void Game::mouseReleaseEvent(QMouseEvent* mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton)
        jumpPressed = false;
}


/* This is the main loop function, every change in the game happens
   here. */
void Game::timeoutSlot() {
    /* Handle keypresses */
    if (jumpPressed) {
        _player.jump();
    }

    /* Internal state update */
    _player.update(jumpPressed);

    _obstacleManager.update(_laser.y());
    _laser.update(_player.y());

    /* Score update */
    updateScore((unsigned int)_player.y());

    /* Check for eventual collisions */
    collisions();

    /* OpenGL update */
    updateGL();
}

void Game::initializeGL() {
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
}

void Game::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
}

void Game::paintGL() {
    Scene::draw(this);
}

void Game::updateScore(unsigned int s) {
    if (_level < (s / 10)) { /* If we passed a level */
        _level = s / 10;
        _obstacleManager.updateObstacleLevel(_level);
    }
    _currentScore = s;
    if (s > _maxScore)
        _maxScore = s;
}

void Game::collisions() {
    bool collide = false;

    /* Check obstacle collisions */
    for (Obstacle& obs : obstacles())
        if (_player.collision(obs)) {
            collide = true;
            break;
        }

    /* Check laser collision */
    collide = collide || (_laser.y() > _player.y() - _player.h());

    if (collide) {
        std::cout << "End of game at level "
                      << _level
                      << " (" << _player.y() << "m)."
                      << std::endl;
        reset();
    }
}
