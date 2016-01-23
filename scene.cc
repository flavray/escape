#include "scene.h"

#include "player.h"

#include <QtOpenGL>

// Main drawing routine
void Scene::draw(Game* game) {
    glColor3f(0.0f, 1.0f, 0.0f);

    // Left side
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(LEFT_SIDE, -1.0f);
        glVertex2f(LEFT_SIDE,  1.0f);
        glVertex2f(-1.0f,  1.0f);
    glEnd();

    // Right side
    glBegin(GL_QUADS);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(RIGHT_SIDE, -1.0f);
        glVertex2f(RIGHT_SIDE,  1.0f);
        glVertex2f(1.0f,  1.0f);
    glEnd();

    // Player
    Player player = game->player();
    float halfW = player.w() / 2.0f;
    float halfH = player.h() / 2.0f;

    glColor3f(1.0f, 0.5f, 0.0f);

    glBegin(GL_QUADS);
        glVertex2f(player.x() - halfW, -0.5f - halfH);
        glVertex2f(player.x() + halfW, -0.5f - halfH);
        glVertex2f(player.x() + halfW, -0.5f + halfH);
        glVertex2f(player.x() - halfW, -0.5f + halfH);
    glEnd();

    // Mock obstacles - To be changed
    glColor3f(0.5f, 0.5f, 1.0f);

    float myY = 0.5f - player.y();

    glBegin(GL_QUADS);
        glVertex2f(-0.55f, myY - 0.1f);
        glVertex2f(-0.50f, myY - 0.1f);
        glVertex2f(-0.50f, myY + 0.1f);
        glVertex2f(-0.55f, myY + 0.1f);
    glEnd();

    myY = 1.25f - player.y();

    glBegin(GL_QUADS);
        glVertex2f(0.50f, myY - 0.1f);
        glVertex2f(0.55f, myY - 0.1f);
        glVertex2f(0.55f, myY + 0.1f);
        glVertex2f(0.50f, myY + 0.1f);
    glEnd();
}
