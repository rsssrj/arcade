#include <GL/glut.h>
#include <cmath>
#include "player.h"
#include "npc.h"  // Include the header file for NPC

const float velocity = 60.0f;
const float initialSize = 1.0f;  // Initial size of the player blob

// Declare the npcs vector
std::vector<NPC> npcs;
std::vector<NPC> food;

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
            if (it->size > size) {
                setGameOver(true);
                break;
            } else {
                // Player ate the NPC, increase player size by a percentage of NPC size
                float growthPercentage = 0.1f;  // Adjust this value as needed
                size += it->size * growthPercentage;

                // Remove the eaten NPC from the collection
                addBlob(size * 1.25);
                it = npcs.erase(it);
            }
        } else {
            ++it; // Move to the next NPC
        }
    }

    for (auto it = food.begin(); it != food.end();) {
        if (it->checkCollision(*this)) {
            float growthPercentage = 0.1f;  // Adjust this value as needed
            size += it->size * growthPercentage;
            
            // Remove the eaten NPC from the collection
                addFood();
                it = food.erase(it);
        } 
        
        else {
            ++it; // Move to the next NPC
        }
    }
    


    glutPostRedisplay(); // Trigger a redraw
}

void player::addBlob(float size)
{
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    float startX = static_cast<float>(rand() % windowWidth - windowWidth / 2);
    float startY = static_cast<float>(rand() % windowHeight - windowHeight / 2);
    float startVelocity = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f + 1.0f;
    //elapsedTime = 0;
    npcs.emplace_back(startX, startY, startVelocity, size);

}
void player::addFood() {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    float startX = static_cast<float>(rand() % windowWidth - windowWidth / 2);
    float startY = static_cast<float>(rand() % windowHeight - windowHeight / 2);
    //float startVelocity = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f + 1.0f;
    //elapsedTime = 0;
    food.emplace_back(startX, startY, 0.0f, 4.0f);
}

bool player::isGameOver()
{
    return gameOver;
}

void player::setGameOver(bool x)
{
    gameOver = x;
}


void player::setSize(float x)
{
    size = x;
}

