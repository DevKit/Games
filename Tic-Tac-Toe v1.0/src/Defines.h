#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED


// Screen width
#define SCREEN_W 680
// Screen height
#define SCREEN_H 360
// Screen (bits per pixel) color depth
#define BPP       32

// Size of text buffers for the game statistics
#define S_SIZE 5

// Size of the game board dimensions
#define ROWS 3
#define COLS 3

#define NUMBER_OF_FONTS    2
#define NUMBER_OF_IMAGES   7
#define NUMBER_OF_STRINGS 11

// Coordinates of the various buttons in the game
#define MAIN_P1   SCREEN_W - 435, SCREEN_H - 130, static_cast <Uint16> (iD[3] -> w), static_cast <Uint16> (iD[3]  -> h)
#define MAIN_P2   SCREEN_W - 435, SCREEN_H - 90,  static_cast <Uint16> (iD[3] -> w), static_cast <Uint16> (iD[3]  -> h)
#define MAIN_EXIT SCREEN_W - 435, SCREEN_H - 50,  static_cast <Uint16> (iD[3] -> w), static_cast <Uint16> (iD[3]  -> h)
#define TO_MAIN   SCREEN_W - 200, SCREEN_H - 150, static_cast <Uint16> (iD[2] -> w), static_cast <Uint16> (iD[2] -> h)
#define RESTART   SCREEN_W - 200, SCREEN_H - 100, static_cast <Uint16> (iD[2] -> w), static_cast <Uint16> (iD[2] -> h)
#define QUIT      SCREEN_W - 200, SCREEN_H - 50,  static_cast <Uint16> (iD[2] -> w), static_cast <Uint16> (iD[2] -> h)

// Coordinates of the game board
#define BOARD  0,    0, 480, 360

// Coordinates of the segments that form the game board
#define BLOCK1 0,    0, 150, 120
#define BLOCK2 70,   0, 260, 120
#define BLOCK3 140,  0, 360, 120
#define BLOCK4 0,   70, 150, 170
#define BLOCK5 70,  70, 265, 170
#define BLOCK6 140, 70, 510, 170
#define BLOCK7 0, 0, 145, 500
#define BLOCK8 120, 0, 220, 500
#define BLOCK9 260, 0, 200, 500


#endif // DEFINES_H_INCLUDED


