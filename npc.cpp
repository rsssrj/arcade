#include <GL/glut.h>
#include <cmath>
#include "npc.h"

void NPC::moveRandomly(int deltaTime) {
    moveTimer -= deltaTime;

    if (moveTimer <=0) {
        randomAngle = static_cast<float>(rand() % 360);

        // Calculate the movement components based on the random angle
        moveTimer = moveDuration;
    }

    float deltaX = velocity * cosf(randomAngle);
    float deltaY = velocity * sinf(randomAngle);

    // Move the NPC
    move(deltaX, deltaY, deltaTime);
}