#ifndef NPC_H
#define NPC_H

class player;  // Forward declaration

#include "blob.h"

class NPC : public blob {
private:
    int moveTimer;
    int moveDuration;
    float randomAngle;

public:
    NPC(float startX, float startY, float startVelocity, float startSize)
        : blob(startX, startY, startVelocity, startSize) {
        moveDuration = rand() % 12000 + 2000;
        moveTimer = 0;
    }

    void moveRandomly(player& playerBlob, int deltaTime);
};

#endif // NPC_H
