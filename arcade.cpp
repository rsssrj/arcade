#include <GL/glut.h>
#include "npc.h"
#include "player.h"


player playerBlob(0.0f, 0.0f, 2.0f);
std::vector<NPC> npcs;

void initializeNPCs() {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // Create NPC blobs with random positions and velocities
    for (int i = 0; i < 15; ++i) {
        float startX = static_cast<float>(rand() % windowWidth - windowWidth / 2);  // Random X position between -width/2 and width/2
        float startY = static_cast<float>(rand() % windowHeight - windowHeight / 2);  // Random Y position between -height/2 and height/2
        float startVelocity = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f + 1.0f;  // Random velocity between 1 and 3
        npcs.emplace_back(startX, startY, startVelocity);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Render the player blob
    playerBlob.display();

    // Render each NPC in the collection
    for (const auto& npc : npcs) {
        npc.display();
    }

    glutSwapBuffers();
}

void timer(int value) {
    // Move each NPC randomly
    for (auto& npc : npcs) {
        npc.moveRandomly(16);
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
    glutCreateWindow("Blob Game");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mouseMotion);  // Use passive motion callback to track mouse movement without button press

    initializeNPCs();  // Initialize the collection of NPC blobs

    glutTimerFunc(0, timer, 0);  // Start the update timer
    srand(static_cast<unsigned>(time(0)));  // Seed the random number generator
    glutMainLoop();
}