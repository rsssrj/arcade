#include <GL/glut.h>
#include <cmath>
#include "blob.h"

void blob::move(float deltaX, float deltaY, int deltaTime) {
    x += deltaX;
    y += deltaY;
}

void blob::display() const {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // Increase the size of the blob (adjust the scaling factor as needed)
    glScalef(size, size, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);  // Center of the circle
    for (int i = 0; i <= 360; ++i) {
        float radian = static_cast<float>(i) * 3.1415926f / 180.0f;
        glVertex2f(cosf(radian), sinf(radian));
    }
    glEnd();

    glPopMatrix();
}

bool blob::checkCollision(const blob& other) const {
    if (x == other.x || y == other.y)
        return true;
    float distance = sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    return distance < (size + other.size);
}


