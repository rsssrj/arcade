#ifndef PLAYER_H
#define PLAYER_H

#include "blob.h"
#include "npc.h"  // Include the header file for NPC

// Declare the extern variables in the header
extern std::vector<NPC> npcs;
extern std::vector<NPC> food;
extern int elapsedTime;

class player : public blob {
public:
    player(float startX, float startY, float startVelocity, float startSize)
        : blob(startX, startY, startVelocity, startSize) {}

    // Function to handle player movement based on mouse input
    void moveMouse(int x, int y);
    void addBlob(float size);
    bool isGameOver();
    void setGameOver(bool x);
    void setSize(float x);
    void addFood();
private: 
    bool gameOver = false;
};

#endif // PLAYER_H


