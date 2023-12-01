#include <GL/glut.h>
#include <cmath>
#include "player.h"


const float velocity = 3.0f;

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

        // Move the circle with constant velocity in the direction of the cursor
        this->x += directionX * velocity;
        this->y += directionY * velocity;
    }
    
    glutPostRedisplay(); // Trigger a redraw
}