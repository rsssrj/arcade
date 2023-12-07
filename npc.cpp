#include <GL/glut.h>
#include <cmath>
#include "npc.h"

void NPC::moveRandomly(int deltaTime) {
    moveTimer -= deltaTime;

    if (moveTimer <= 0) {
        randomAngle = static_cast<float>(rand() % 360);

        // Calculate the movement components based on the random angle
        moveTimer = moveDuration;
    }

    float windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    float windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    if (x < -windowWidth / 2.0f || x > windowWidth / 2.0f) {
        randomAngle = 180.0f - randomAngle;  // Reverse the angle to bounce back
    }

    if (y < -windowHeight / 2.0f || y > windowHeight / 2.0f) {
        randomAngle = -randomAngle;  // Reverse the angle to bounce back
    }

    float deltaX = velocity * cosf(randomAngle);
    float deltaY = velocity * sinf(randomAngle);

    // Update the NPC's position
    move(deltaX, deltaY, deltaTime);
}
