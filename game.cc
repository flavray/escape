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
    }
}

void Game::keyReleaseEvent(QKeyEvent* keyEvent) {
    switch (keyEvent->key()) {
    case Qt::Key_Space:
        jumpPressed = false;
        break;
    }
}

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

    std::cout << maxScore() << std::endl;

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
    glClear(GL_COLOR_BUFFER_BIT);

    Scene::draw(this);
}

void Game::updateScore(unsigned int s) {
    _currentScore = s;
    if (s > _maxScore)
        _maxScore = s;
}
