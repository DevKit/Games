#ifndef TYPEDEFS_H_INCLUDED
#define TYPEDEFS_H_INCLUDED


#include "Defines.h"


typedef std::array <TTF_Font*, NUMBER_OF_FONTS>      fArr; // Fonts with different sizes
typedef std::array <SDL_Surface*, NUMBER_OF_IMAGES>  iArr; // Images
typedef std::array <SDL_Surface*, NUMBER_OF_STRINGS> tArr; // Text


typedef enum
{
    EMPTY,
    X_MARK,
    O_MARK
} Mark;


typedef enum
{
    X_GAME,
    O_GAME,
    TIE_GAME
} GameOutcome;


typedef struct
{
    Uint8 row, col;
} Position;


#endif // TYPEDEFS_H_INCLUDED
