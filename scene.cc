#include "scene.h"

#include "player.h"

#include <QtOpenGL>

#include <iostream>

// Main drawing routine
void Scene::draw(Game* game) {
    glColor3f(0.0f, 1.0f, 0.0f);

    // Left side
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(LEFT_SIDE, 1.0f);
        glVertex2f(LEFT_SIDE, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();

    // Right side
    glBegin(GL_QUADS);
        glVertex2f(RIGHT_SIDE, 1.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(RIGHT_SIDE, -1.0f);
    glEnd();

    // Player
    Player player = game->player();
    float halfW = player.w() / 2.0f;
    float halfH = player.h() / 2.0f;

    glColor3f(1.0f, 0.5f, 0.0f);

    glBegin(GL_QUADS);
        glVertex2f(player.x() - halfW, -0.5f + halfH);
        glVertex2f(player.x() + halfW, -0.5f + halfH);
        glVertex2f(player.x() + halfW, -0.5f - halfH);
        glVertex2f(player.x() - halfW, -0.5f - halfH);
    glEnd();

    // Obstacles
    glColor3f(0.5f, 0.5f, 1.0f);

    for (Obstacle obstacle : game->obstacles()) {
        float myY = obstacle.y() - player.y() - 0.5f;

        halfW = obstacle.w() / 2.0f;
        halfH = obstacle.h() / 2.0f;

        if (player.collision(obstacle))
            glColor3f(1.0f, 0.0f, 1.0f);
        else
            glColor3f(0.5f, 0.5f, 1.0f);

        glBegin(GL_QUADS);
            glVertex2f(obstacle.x() - halfW, myY + halfH);
            glVertex2f(obstacle.x() + halfW, myY + halfH);
            glVertex2f(obstacle.x() + halfW, myY - halfH);
            glVertex2f(obstacle.x() - halfW, myY - halfH);
        glEnd();
    }
}
