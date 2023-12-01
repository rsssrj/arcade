#ifndef BLOB_H
#define BLOB_H


#include <GL/glut.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>

class blob {
public:
    float x, y;  // blob position
    float velocity;  // blob velocity

    blob(float startX, float startY, float startVelocity) : x(startX), y(startY), velocity(startVelocity) {}

    // Function to move the blob
    void move(float deltaX, float deltaY, int deltaTime);

    // Function to display blob information
    void display() const; 
};

#endif // BLOB_H