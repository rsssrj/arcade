#include <GL/glut.h>
#include <cmath>
#include "player.h"
#include "npc.h"  // Include the header file for NPC

const float velocity = 3.0f;
const float initialSize = 1.0f;  // Initial size of the player blob

// Declare the npcs vector
std::vector<NPC> npcs;

void player::moveMouse(int x, int y) {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // Convert mouse coordinates to OpenGL coordinates
    float targetX = (x - windowWidth / 2.0f);
    float targetY = (windowHeight / 2.0f - y);

    // Calculate the direction vector
    float directionX = targetX - this->x;
    float directionY = targetY - this->y;

    // Calculate the distance to the target
    float distance = sqrt(directionX * directionX + directionY * directionY);

    // Check if the distance is not zero
    if (distance > 0) {
        // Normalize the direction vector
        directionX /= distance;
        directionY /= distance;

        // Move the player blob with constant velocity in the direction of the cursor
        this->x += directionX * velocity;
        this->y += directionY * velocity;
    }

    // Check for collisions with NPC blobs
    for (auto it = npcs.begin(); it != npcs.end();) {
        if (it->checkCollision(*this)) {
            // Player ate the NPC, increase player size
            size += it->size;

            // Remove the eaten NPC from the collection
            it = npcs.erase(it);
        } else {
            ++it; // Move to the next NPC
        }
    }

    glutPostRedisplay(); // Trigger a redraw
}

