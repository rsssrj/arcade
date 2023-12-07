#include <GL/glut.h>
#include <cmath>
#include "npc.h"
#include "player.h"

extern player playerBlob;


void NPC::moveRandomly(player& playerBlob, int deltaTime) {
    moveTimer -= deltaTime;

    if (moveTimer <= 0) {
        // Calculate the direction vector towards the player
        float deltaX = playerBlob.x - x;
        float deltaY = playerBlob.y - y;

        // Calculate the angle
        randomAngle = atan2(deltaY, deltaX) * 180.0f / 3.1415926f;

        // Calculate the movement components based on the angle
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

    // Check for collisions with other NPCs
    for (auto& otherNPC : npcs) {
        if (&otherNPC != this && checkCollision(otherNPC)) {
            if (size > otherNPC.size) {
                // This NPC ate the other NPC
                size += otherNPC.size * 0.5f;  // Adjust the growth percentage
                otherNPC.size = 0;  // Mark the other NPC as eaten
            } else if (size < otherNPC.size) {
                // This NPC got eaten by the other NPC
                otherNPC.size += size * 0.5f;  // Adjust the growth percentage
                size = 0;  // Mark this NPC as eaten
            }
        }
    }
}
