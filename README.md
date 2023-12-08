# Arcading

## Game Description
The objective of this project is to develop an intense game 2D game using OpenGL and GLUT where the player controls a green blob (the playerBlob) that moves in response to mouse movements. The objective of the game is to avoid or consume blue blobs (NPCs) and stationary red blobs (food). The player's blob grows larger by consuming smaller NPCs, while collisions with larger NPCs or the game boundary can result in game over.

Here's a brief description of the game's components:

Player Blob (Green):

The playerBlob is controlled by the player's mouse movements.
The player can navigate the blob across the game window.
Non-Player Characters (NPCs - Blue):

There are 35 NPCs that spawn very frequently (every second) with random positions, velocities, and sizes.
NPCs move randomly within the game window.
The playerBlob can consume NPCs by colliding with them, resulting in the playerBlob growing in size.
Stationary Food (Red):

There are 100 stationary food blobs that don't move (stationary NPCs).
The playerBlob can consume stationary food, causing the playerBlob to grow in size.
Game Mechanics:

The game includes a timer displayed at the top-center of the window, counting down from 1 minute.
The game ends if the playerBlob collides with a larger NPC or if there are no NPCs left to consume.
Players can restart the game by pressing 'R' and exit the game by pressing 'Q'.
Visuals:

The game window uses OpenGL for rendering and displays a white background.
The playerBlob is drawn in green, NPCs in blue, and stationary food in red.
The game includes a "Game Over" screen with information on how to restart or quit the game.

Players aim to survive as long as possible, growing their playerBlob by consuming smaller NPCs while avoiding larger NPCs and collisions that would end the game. The spawning frequency of NPCs, their random movement, and the constant growth of the playerBlob contribute to the dynamics of the game.

To do this, we've implemented **player.cpp**, **player.h** files and **npc.cpp, npc.h** files for dictating the movement of the player and npc blobs respectively. The player blob is controlled by the user. The **game.h, game.cpp** files combine these movements together on the screen and, **arcade.cpp** is the main file which makes the entire program run.

## Compilation
To compile this project, type make and then **./arcade** in the terminal. Then, move your mouse to move around and try to accumulate as much mass as possible.
