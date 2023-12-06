#ifndef PLAYER_H
#define PLAYER_H

#include "blob.h"
#include "npc.h"  // Include the header file for NPC

// Declare the extern variable in the header
extern std::vector<NPC> npcs;

class player : public blob {
public:
    player(float startX, float startY, float startVelocity, float startSize)
        : blob(startX, startY, startVelocity, startSize) {}

    // Function to handle player movement based on mouse input
    void moveMouse(int x, int y);
    void addBlob(float size);
};

#endif // PLAYER_H

