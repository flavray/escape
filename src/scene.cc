#include "scene.h"

#include "player.h"

Image* Scene::_digitsImage = NULL;

// Main drawing routine
void Scene::draw(Game* game) {
    if (!_digitsImage)
        _digitsImage = new Image("assets/digits.png");

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.11f, 0.11f, 0.11f);

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

    glColor3f(0.85f, 0.79f, 0.61f);

    glBegin(GL_QUADS);
    glVertex2f(player.x() - halfW, -0.5f + halfH);
    glVertex2f(player.x() + halfW, -0.5f + halfH);
    glVertex2f(player.x() + halfW, -0.5f - halfH);
    glVertex2f(player.x() - halfW, -0.5f - halfH);
    glEnd();

    // Obstacles
    glColor3f(0.85f, 0.79f, 0.61f);

    for (Obstacle obstacle : game->obstacles()) {
        float myY = obstacle.y() - player.y() - 0.5f;

        halfW = obstacle.w() / 2.0f;
        halfH = obstacle.h() / 2.0f;

        if (player.collision(obstacle))
            glColor3f(0.86f, 0.2f, 0.13f);
        else
            glColor3f(0.85f, 0.79f, 0.61f);

        glBegin(GL_QUADS);
        glVertex2f(obstacle.x() - halfW, myY + halfH);
        glVertex2f(obstacle.x() + halfW, myY + halfH);
        glVertex2f(obstacle.x() + halfW, myY - halfH);
        glVertex2f(obstacle.x() - halfW, myY - halfH);
        glEnd();
    }

    // Laser
    glColor3f(0.86f, 0.2f, 0.13f);

    float laserY = game->laser().y() - player.y() - 0.5f;

    if (game->laser().y() > player.y() - player.h())
        glColor3f(1.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
    glVertex2f(LEFT_SIDE, laserY);
    glVertex2f(RIGHT_SIDE, laserY);
    glVertex2f(RIGHT_SIDE, laserY - 0.05f);
    glVertex2f(LEFT_SIDE, laserY - 0.05f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
    glVertex2f(LEFT_SIDE - 0.06f, laserY + 0.03f);
    glVertex2f(LEFT_SIDE, laserY);
    glVertex2f(LEFT_SIDE, laserY - 0.05f);
    glVertex2f(LEFT_SIDE - 0.06f, laserY - 0.08f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(RIGHT_SIDE, laserY);
    glVertex2f(RIGHT_SIDE + 0.06f, laserY + 0.03f);
    glVertex2f(RIGHT_SIDE + 0.06f, laserY - 0.08f);
    glVertex2f(RIGHT_SIDE, laserY - 0.05f);
    glEnd();

    /* Score and max score */
    _digitsImage->prepaint();

    glColor3f(1.0f, 1.0f, 1.0f);

    unsigned int score = game->score();
    int i = 0;
    while (score > 0) {
        int digit = score % 10;

        float width = 0.1f;
        float x = digit * width;

        glBegin(GL_QUADS);

        glTexCoord2f(x, 0.0f);
        glVertex2f(0.9 - 0.08 * i, 0.8);

        glTexCoord2f(x + width, 0.0f);
        glVertex2f(0.9 - 0.08 * (i - 1), 0.8);

        glTexCoord2f(x + width, 1.0f);
        glVertex2f(0.9 - 0.08 * (i - 1), 0.88);

        glTexCoord2f(x, 1.0f);
        glVertex2f(0.9 - 0.08 * i, 0.88);

        glEnd();

        score /= 10;
        i++;
    }

    unsigned int mscore = game->maxScore();
    i = 0;
    while (mscore > 0) {
        int digit = mscore % 10;

        float width = 0.1f;
        float x = digit * width;

        glBegin(GL_QUADS);

        glTexCoord2f(x, 0.0f);
        glVertex2f(0.9 - 0.08 * i, 0.7);

        glTexCoord2f(x + width, 0.0f);
        glVertex2f(0.9 - 0.08 * (i - 1), 0.7);

        glTexCoord2f(x + width, 1.0f);
        glVertex2f(0.9 - 0.08 * (i - 1), 0.78);

        glTexCoord2f(x, 1.0f);
        glVertex2f(0.9 - 0.08 * i, 0.78);

        glEnd();

        mscore /= 10;
        i++;
    }

    glDisable(GL_TEXTURE_2D);
}
