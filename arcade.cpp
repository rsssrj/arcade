#include <GL/glut.h>
#include <cmath>

const float circleRadius = 20.0f;  // Specify the radius in pixels
//const float mouseMoveScale = 10.0f;

float circleX = 0.0f;
float circleY = 0.0f;

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the moving circle with a fixed radius in pixels
    drawCircle(circleX, circleY, circleRadius, 100);

    glutSwapBuffers();
}


void mouseMotion(int x, int y) {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    // Convert mouse coordinates to OpenGL coordinates
    circleX = (x - windowWidth / 2.0f);
    circleY = (windowHeight / 2.0f - y);

    // Apply bounds to keep the circle within a reasonable area
    float maxX = windowWidth / 2.0f - circleRadius;
    float maxY = windowHeight / 2.0f - circleRadius;
    float minX = -windowWidth / 2.0f + circleRadius;
    float minY = -windowHeight / 2.0f + circleRadius;

    if (circleX > maxX) circleX = maxX;
    if (circleX < minX) circleX = minX;
    if (circleY > maxY) circleY = maxY;
    if (circleY < minY) circleY = minY;

    glutPostRedisplay(); // Trigger a redraw
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Move Circle with Mouse");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mouseMotion); // Use passive motion callback to track mouse movement without button press
    glutMainLoop();
    return 0;
}