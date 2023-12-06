#ifndef NPC_H
#define NPC_H

#include "blob.h"

class NPC : public blob {
private:
    int moveTimer;     // Timer to control how long the NPC moves in a certain direction
    int moveDuration;  // How long the NPC should move in a certain direction (in milliseconds)
    float randomAngle;

public:
    NPC(float startX, float startY, float startVelocity, float startSize)
        : blob(startX, startY, startVelocity, startSize) {
        moveDuration = rand() % 17000 + 3000;
        moveTimer = 0;
    }

    // Function to make NPC move randomly
    void moveRandomly(int deltaTime);
};

#endif // NPC_H

