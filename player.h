#ifndef PLAYER_H
#define PLAYER_H

#include "blob.h"

class player : public blob {
public:
    player(float startX, float startY, float startVelocity) : blob(startX, startY, startVelocity) {}

    // Function to handle player movement based on mouse input
    void moveMouse(int x, int y);
};

#endif // PLAYER_H