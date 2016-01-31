#include "game.h"

#include "scene.h"

#include <QtOpenGL>
#include <QGLFunctions>
#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

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

void Game::setFont(FT_Face font) {
    _font = font;
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
    initializeGLFunctions();
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
}

void Game::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
}

void Game::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint texture[1] = {0};

    Scene::draw(this);

    glShadeModel(GL_FLAT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    FT_Load_Char(_font, 'A', FT_LOAD_RENDER);
    FT_GlyphSlot g = _font->glyph;

    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RED,
      g->bitmap.width,
      g->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      g->bitmap.buffer
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-0.05f, -0.5f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(0.05f, -0.5f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(0.05f, -0.45f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-0.05f, -0.45f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0f, 1.0f, 1.0f);


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

Game::~Game() {
    /* We need to manually delete the dangling pointer. */
    delete _font;
}
