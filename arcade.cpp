#include <GL/glut.h>
#include <GL/freeglut.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include "npc.h"
#include "player.h"



player playerBlob(0.0f, 0.0f, 2.0f, 15.0f); // Provide a value for startSize, e.g., 1.0f


int elapsedTime = 0;         // Elapsed time in seconds
bool blinkTimer = false;      // Flag to control blinking
int blinkDuration = 10;        // Duration of blinking in seconds

void initializeNPCs() {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // Create stationary small NPCs
    for (int i = 0; i < 100; ++i) {
        float startX = static_cast<float>(rand() % windowWidth - windowWidth / 2);
        float startY = static_cast<float>(rand() % windowHeight - windowHeight / 2);
        float startVelocity = 0.0f;  // Stationary NPCs
        const float startSize = 4.0f;  // Small size for stationary NPCs
        food.emplace_back(startX, startY, startVelocity, startSize);
    }

    // Create NPC blobs with random positions and velocities
    for (int i = 0; i < 35; ++i) {
        float startX = static_cast<float>(rand() % windowWidth - windowWidth / 2);
        float startY = static_cast<float>(rand() % windowHeight - windowHeight / 2);
        float startVelocity = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 3.0f + 2.0f;
        float startSize = static_cast<float>(rand() % 40 + 10);  // Set the initial size for NPCs
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
    sprintf(timerText, "%01d:%02d", (60 - elapsedTime / 60), 59 - (elapsedTime % 60));
    for (int i = 0; i < strlen(timerText); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, timerText[i]);
    }

    glPopMatrix();
}







void restartGame()
{
    playerBlob.setSize(15.0f);
    npcs.clear();
    food.clear();
    elapsedTime = 0;
    initializeNPCs();
    playerBlob.setGameOver(false);


}

void keyboard(unsigned char key, int x, int y) {
    if (playerBlob.isGameOver() && key == 'r') {
        restartGame();
        glutPostRedisplay(); // Trigger a redraw to update the display
    }
        if (playerBlob.isGameOver() && key == 'q') {
        exit(0);
    }
}

void endScreen()
{
    glLoadIdentity();
    // Choose a larger font size, e.g., GLUT_BITMAP_HELVETICA_24

    char textString[100]; // Assuming a buffer size of 50 is sufficient
    sprintf(textString, "Game Over\n Press 'R' to Restart and 'Q' to quit\nScore: %.2f", playerBlob.size);
    // Display text on the screen
    glColor3f(0.0f, 0.0f, 0.0f); // Set color to black
    glRasterPos2f(0.0f, 0.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)textString);

    
}




void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Set the clear color to white (R, G, B, A)
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Render the player blob in a different color (e.g., green)
    glColor3f(0.0f, 1.0f, 0.0f);  // Green color
    playerBlob.display();

    // Render each NPC in the collection with the original color (e.g., blue)
    if (!playerBlob.isGameOver()) {
        glColor3f(0.0f, 0.0f, 1.0f);  // Blue color
        for (const auto& npc : npcs) {
            npc.display();
        }

        for (const auto& npc : food) {
            npc.display();
        }

        // Draw the timer only if it's not blinking
        if (!blinkTimer) {
            drawTimer();
        }
    }
    
    else {
        endScreen();
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

    // Check if 10 seconds have passed
    if (elapsedTime >= 10 * 60) {  // 10 seconds * 60 frames per second
        // Exit the program
        exit(0);
    }

    // Check if the player has eaten an NPC
    if (npcs.empty()) {
        // Exit the program if there are no more NPCs
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
    glutKeyboardFunc(keyboard); // Register the keyboard function

    initializeNPCs();

    glutTimerFunc(0, timer, 0);
    srand(static_cast<unsigned>(time(0)));
    glutMainLoop();
}

