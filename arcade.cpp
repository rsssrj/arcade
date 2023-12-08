#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include "npc.h"
#include "player.h"



player playerBlob(0.0f, 0.0f, 2.0f, 15.0f); // Provide a value for startSize, e.g., 1.0f

int spawnTimer = 0;          // Timer for spawning NPCs
int spawnInterval = 10 * 60;  // Spawn a new NPC every 5 seconds (5 * 60 frames per second)

int elapsedTime = 0;         // Elapsed time in seconds
bool blinkTimer = false;      // Flag to control blinking
int blinkDuration = 10;        // Duration of blinking in seconds
int totalGameTime = 10*60;  // Total game time in seconds

void initializeNPCs() {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // Create stationary small NPCs
    for (int i = 0; i < 100; ++i) {
        float startX = static_cast<float>(rand() % windowWidth - windowWidth / 2);
        float startY = static_cast<float>(rand() % windowHeight - windowHeight / 2);
        float startVelocity = 0.0f;  // Stationary NPCs
        float startSize = static_cast<float>(rand() % 5 + 2);  // Small size for stationary NPCs
        npcs.emplace_back(startX, startY, startVelocity, startSize);
    }

    // Create NPC blobs with random positions and velocities
    for (int i = 0; i < 15; ++i) {
        float startX = static_cast<float>(rand() % windowWidth - windowWidth / 2);
        float startY = static_cast<float>(rand() % windowHeight - windowHeight / 2);
        float startVelocity = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f + 1.0f;
        float startSize = static_cast<float>(rand() % 20 + 5);  // Set the initial size for NPCs
        npcs.emplace_back(startX, startY, startVelocity, startSize);
    }
}



void drawTimer() {
    glPushMatrix();
    glLoadIdentity();

    // Set the raster position for the timer text at the center-top of the screen
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glRasterPos2f(-40.0f, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f - 20.0f);

    // Draw the dynamic part of the timer text (counting backward)
    char timerText[10];
    sprintf(timerText, "%02d:%02d", totalGameTime / 60, totalGameTime - (elapsedTime % 60));
    for (int i = 0; i < strlen(timerText); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, timerText[i]);
    }

    glPopMatrix();
}







void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Set the clear color to white (R, G, B, A)
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Render the player blob in a different color (e.g., green)
    glColor3f(0.0f, 1.0f, 0.0f);  // Green color
    playerBlob.display();

    // Render each NPC in the collection with the original color (e.g., blue)
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue color
    for (const auto& npc : npcs) {
        npc.display();
    }

    // Draw the timer only if it's not blinking
    if (!blinkTimer) {
        drawTimer();
    }

    glutSwapBuffers();
}



// Update the timer function
void timer(int value) {
    // Move each NPC randomly and check for collisions
    for (auto& npc : npcs) {
        npc.moveRandomly(playerBlob, 16);

        // Check for collisions with other NPCs
        for (auto& otherNPC : npcs) {
            if (&otherNPC != &npc && npc.checkCollision(otherNPC)) {
                if (npc.size > otherNPC.size) {
                    // This NPC ate the other NPC
                    npc.size += otherNPC.size * 0.5f;  // Adjust the growth percentage
                    otherNPC.size = 0;  // Mark the other NPC as eaten
                    elapsedTime = 0;  // Reset the timer when NPC is eaten
                    totalGameTime = 10 * 60;  // Reset totalGameTime to 10 seconds

                    
                } else if (npc.size < otherNPC.size) {
                    // This NPC got eaten by the other NPC
                    otherNPC.size += npc.size * 0.5f;  // Adjust the growth percentage
                    npc.size = 0;  // Mark this NPC as eaten
                }
            }
        }
    }

    // Update the elapsed time
    elapsedTime++;

    // Check if the player has eaten an NPC
    if (npcs.empty()) {
        // Exit the program if there are no more NPCs
        exit(0);
    }

    // Check if the time has run out
    if (elapsedTime >= totalGameTime) {
        // Exit the program if no NPC was eaten within the time limit
        exit(0);
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);  // 60 FPS update rate
}






void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void mouseMotion(int x, int y) {
    playerBlob.moveMouse(x, y);
    //glutPostRedisplay(); // Trigger a redraw
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    
    // Use glutGet(GLUT_SCREEN_WIDTH) and glutGet(GLUT_SCREEN_HEIGHT) to get the screen dimensions
    glutCreateWindow("Blob Game");
    glutFullScreen();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mouseMotion);

    initializeNPCs();

    glutTimerFunc(0, timer, 0);
    srand(static_cast<unsigned>(time(0)));
    glutMainLoop();
}
