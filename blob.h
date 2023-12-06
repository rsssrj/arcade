#ifndef BLOB_H
#define BLOB_H

#include <GL/glut.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>

class blob {
public:
    float x, y;       // blob position
    float velocity;    // blob velocity
    float size;        // blob size

    blob(float startX, float startY, float startVelocity, float startSize)
        : x(startX), y(startY), velocity(startVelocity), size(startSize) {}

    // Function to move the blob
    void move(float deltaX, float deltaY, int deltaTime);

    // Function to display blob information
    void display() const;

    // Function to check if the blob has eaten another blob
    bool checkCollision(const blob& other) const;
};

#endif // BLOB_H
