#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include "npc.h"
#include "player.h"
#include <iostream>
#include <GL/freeglut.h>

player playerBlob(0.0f, 0.0f, 2.0f, 10.0f);  // Provide a value for startSize, e.g., 1.0f

int elapsedTime = 0;         // Elapsed time in seconds
bool blinkTimer = false;      // Flag to control blinking
int blinkDuration = 3;        // Duration of blinking in seconds

void initializeNPCs() {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

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
    sprintf(timerText, "%01d:%02d", (60 - elapsedTime / 60), 59 - (elapsedTime % 60));
    for (int i = 0; i < strlen(timerText); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, timerText[i]);
    }

    glPopMatrix();
}


// Function to handle the end screen display
void endScreen()
{
    glLoadIdentity();


    // Display text on the screen
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white
    glRasterPos2f(-0.5, 0.5);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Game Over");
    glutSwapBuffers();
}


void restartGame() {
    // Reset relevant game state here
    elapsedTime = 0;
    blinkTimer = false;
    playerBlob.setGameOver(false);
    initializeNPCs();
}

void keyboard(unsigned char key, int x, int y) {
    if (playerBlob.isGameOver())
    {
        if (key == 'q' || key == 'Q') {
            glutLeaveMainLoop();
        } else if (key == 'r' || key == 'R') {
            // Restart the game
            restartGame();
            glutPostRedisplay();
        }
    }
}



void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    if(!playerBlob.isGameOver())
    {

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
    else
    {
        endScreen();
    }
}


void timer(int value) {
    if (!playerBlob.isGameOver())
    {
        // Move each NPC randomly
        for (auto& npc : npcs) {
            npc.moveRandomly(16);
        }

        // Update the elapsed time
        elapsedTime++;

        // Check if 60 seconds have passed
        if (elapsedTime >= 60 * 60) {  // 60 seconds * 60 frames per second
            // Exit the program
            playerBlob.setGameOver(true);
        }

        glutPostRedisplay();
        glutTimerFunc(16, timer, 0);  // 60 FPS update rate
    }
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
    glutPostRedisplay(); // Trigger a redraw
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Blob Game");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mouseMotion);  // Use passive motion callback to track mouse movement without button press
    glutKeyboardFunc(keyboard); // use to reset game
    glutIdleFunc(idle);


    initializeNPCs();  // Initialize the collection of NPC blobs

    glutTimerFunc(0, timer, 0);  // Start the update timer
    srand(static_cast<unsigned>(time(0)));  // Seed the random number generator
    glutMainLoop();
    return 0;
}
