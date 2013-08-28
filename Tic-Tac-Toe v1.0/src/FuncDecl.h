#ifndef FUNCDECL_H_INCLUDED
#define FUNCDECL_H_INCLUDED


#include "Typedefs.h"
#include "Types.h"


class GameStats;


void initDisplay(iArr&);
void initImageData(iArr&);
void initFontData(fArr&);
void initStringData(tArr&, fArr);
void cleanUp(iArr&, fArr&, tArr&);
void initGameBoard(Mark&);
bool isEmpty(Mark, Position);
bool isFull(Mark);
void updateGameBoard(Mark&, const Position&, Mark);
bool checkVictory(const Mark&, Mark);
bool checkTie(const Mark&);
void updateGameStats(const Mark&, GameStats&);
bool mouseOverArea(const Sint16, const Sint16, const SDL_Rect&);
void drawGameStats(const GameStats&, iArr&, tArr&, fArr&);
void drawMainMenu(const iArr&, const tArr&);
void drawSPlayer(iArr&, const tArr&);
void drawMPlayer(const iArr&, const tArr&);
void logicMainMenu(SDL_Event, GameState&, bool&, iArr iD, tArr tD);
void logicSPlayer(SDL_Event, GameState&, bool&, iArr&, tArr, fArr&, Mark, Mark&, GameStats&);
void logicMPlayer(SDL_Event, GameState&, bool&, iArr, tArr, Mark);
void drawGameStats(const GameStats&, iArr&, tArr&, fArr&);


#endif // FUNCDECL_H_INCLUDED
