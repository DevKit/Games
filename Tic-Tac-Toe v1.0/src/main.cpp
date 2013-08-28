//////////////////////////////////////////////////////
// Name:        main.cpp
// Author:      Fares
// Last Update: 27/08/2013
//////////////////////////////////////////////////////


#include <string>
#include <array>


#include "Exceptions.h"
#include "GameStates.h"
#include "GRoutines.h"
#include "Resources.h"
#include "TextMode.h"
#include "Typedefs.h"
#include "FuncDecl.h"
#include "Defines.h"
#include "Stats.h"
#include "Types.h"


SDL_Surface* RenderTTF(TTF_Font *font, const char *txt, SDL_Color color, TextMode mode)
{
    switch (mode)
    {
        case (SOLID):
            return TTF_RenderText_Solid(font, txt, color);
            break;

        case (SHADED):
            return TTF_RenderText_Shaded(font, txt, color, {83, 220, 49});
            break;

        case (BLENDED):
            return TTF_RenderText_Blended(font, txt, color);
            break;

        default:
            break;
    }
}


//===========================================================================//
// Name: initDisplay
// Parameters: Array of pointers to Surface
// Purpose: Initialize the main surface
// Pre-condition(s): Empty std::array object
// Post-condition(s): None.
//===========================================================================//
void initDisplay(iArr &iD)
{
    iD[0] = SDL_SetVideoMode(SCREEN_W, SCREEN_H, BPP, SDL_SWSURFACE | SDL_DOUBLEBUF);

    if (!iD[0])
    {
        SDL_GetError();
        atexit(SDL_Quit);
    }
}


void initImageData(iArr &iD)
{
    iD[1] = LoadSurface("./images/tttboard.png"); // Load the game board
    iD[2] = LoadSurface("./images/gbutton.png");  // Green button for the in-game modes
    iD[3] = LoadSurface("./images/bbutton.png");  // Blue button for the main menu
    iD[4] = LoadSurface("./images/x.png");
    iD[5] = LoadSurface("./images/o.png");
    // Use this instead of reloading the image on every
    // restart or game state change
    iD[6] = LoadSurface("./images/tttboard.png");
}


void initFontData(fArr &fD)
{
    fD[0] = TTF_OpenFont("./font/arcade.ttf", 90);        // For the title
    fD[1] = TTF_OpenFont("./font/arcade.ttf", 20);        // For the majority of in-game text
}


void initStringData(tArr &tD, fArr fD)
{
    tD[0]  = RenderTTF(fD[0], "TIC   TAC   TOE",    {0xFF, 0xFF, 0xFF}, SOLID);    // The game's title
    tD[1]  = RenderTTF(fD[1], "PLAYER  VS PLAYER",  {0xFF, 0xFF, 0xFF}, SOLID);    // Single player mode
    tD[2]  = RenderTTF(fD[1], "PLAYER VS COMPUTER", {0xFF, 0xFF, 0xFF}, SOLID);    // Two player mode
    tD[3]  = RenderTTF(fD[1], "EXIT",               {0xFF, 0xFF, 0xFF}, SOLID);    // In-menu to exit
    tD[4]  = RenderTTF(fD[1], "PLAYER  1",          {0xFF, 0xFF, 0xFF}, SOLID);
    tD[5]  = RenderTTF(fD[1], "PLAYER  2",          {0xFF, 0xFF, 0xFF}, SOLID);
    tD[6]  = RenderTTF(fD[1], "COMPUTER",           {0xFF, 0xFF, 0xFF}, SOLID);
    tD[7]  = RenderTTF(fD[1], "TIES",               {0xFF, 0xFF, 0xFF}, SOLID);
    tD[8]  = RenderTTF(fD[1], "MAIN MENU",          {0xFF, 0xFF, 0xFF}, SOLID);    // In-game to main menu
    tD[9]  = RenderTTF(fD[1], "QUIT",               {0xFF, 0xFF, 0xFF}, SOLID);    // In-game to exit
    tD[10] = RenderTTF(fD[1], "RESTART",            {0xFF, 0xFF, 0xFF}, SOLID);    // Restart a game
}


void cleanUp(iArr& iD, fArr& fD, tArr& tD)
{
    for (auto &i : iD)
        SDL_FreeSurface(i);

    for (auto &i : fD)
        TTF_CloseFont(i);

    for (auto &i : tD)
        SDL_FreeSurface(i);
}


void initGameBoard(Mark (&game_board)[ROWS][COLS])
{
    for (Uint8 i = 0; i < ROWS; ++i)
        for (Uint8 j = 0; j < COLS; ++j)
            game_board[i][j] = EMPTY;
}


inline bool isEmpty(Mark game_board[][COLS], Position p)
{
    //if (p.col < 0 || p.row < 0)
        //throw Invalid_Position();

    return game_board[p.row][p.col] == EMPTY;
}


bool isFull(const Mark (&game_board)[ROWS][COLS])
{
    for (Uint8 i = 0; i < ROWS; ++i)
        for (Uint8 j = 0; j < COLS; ++j)
            if (game_board[i][j] == EMPTY)
                return false;

    return true;
}


inline void updateGameBoard(Mark (&game_board)[ROWS][COLS], const Position& p, Mark mark)
{
    game_board[p.row][p.col] = mark;
}


bool checkVictory(const Mark (&game_board)[ROWS][COLS], Mark m)
{
    for (Uint8 i = 0; i < ROWS; ++i)
    {
        if ((game_board[i][0] == m && game_board[i][0] == game_board[i][1] && game_board[i][1] == game_board[i][2]) ||
            (game_board[0][i] == m && game_board[0][i] == game_board[1][i] && game_board[1][i] == game_board[2][i]) ||
            (game_board[0][0] == m && game_board[0][0] == game_board[1][1] && game_board[1][1] == game_board[2][2]) ||
            (game_board[0][2] == m && game_board[0][2] == game_board[1][1] && game_board[1][1] == game_board[2][0]))
        {
            return true;
        }
    }

    return false;
}


bool checkTie(const Mark (&game_board)[ROWS][COLS])
{
    return (!checkVictory(game_board, X_MARK) && !checkVictory(game_board, O_MARK) && isFull(game_board));
}


void updateGameStats(const Mark (&game_board)[ROWS][COLS], GameStats& stats)
{
    if (checkVictory(game_board, X_MARK))
    {
        stats.incP1Score();
        //positionCursor()
    }

    else if (checkVictory(game_board, O_MARK))
    {
        stats.incP2Score();
        //positionCursor()
    }

    else if (checkTie(game_board))
    {
        stats.incTie();
        //positionCursor()
    }
}


bool mouseOverArea(const Sint16 mouse_x, const Sint16 mouse_y, const SDL_Rect& button)
{
    return ((mouse_x > button.x) && (mouse_x < button.x + button.w) &&
            (mouse_y > button.y) && (mouse_y < button.y + button.h));
}


void drawGameStats(GameStats& stats, iArr& iD, tArr& tD, fArr& fD)
{
    // Arrays for character stats
    char p1_buff[S_SIZE], p2_buff[S_SIZE], tie_buff[S_SIZE];
    // Temporary surfaces for drawing and updating the scores
    SDL_Surface *p1  = nullptr;
    SDL_Surface *p2  = nullptr;
    SDL_Surface *tie = nullptr;

    snprintf(p1_buff, sizeof(p1_buff), "%u", stats.p1Score());
    p1 = RenderTTF(fD[1], p1_buff, {0xFF, 0xFF, 0xFF}, SOLID);
    PlaceSurface(iD[1] -> w + 95, iD[1] -> h - 330, p1, iD[0], 0);

    snprintf(p2_buff, sizeof(p2_buff), "%u", stats.p2Score());
    p2 = RenderTTF(fD[1], p2_buff, {0xFF, 0xFF, 0xFF}, SOLID);
    PlaceSurface(iD[1] -> w + 95, iD[1] -> h - 280, p2, iD[0], 0);

    snprintf(tie_buff, sizeof(tie_buff), "%u", stats.Tie());
    tie = RenderTTF(fD[1], tie_buff, {0xFF, 0xFF, 0xFF}, SOLID);
    PlaceSurface(iD[1] -> w + 95, iD[1] -> h - 225, tie, iD[0], 0);

    SDL_FreeSurface(p1);
    SDL_FreeSurface(p2);
    SDL_FreeSurface(tie);
}

void drawMainMenu(const iArr &iD, const tArr &tD)
{
    PlaceSurface(SCREEN_W - 605, SCREEN_H - 350, tD[0], iD[0], 0);
    PlaceSurface(SCREEN_W - 435, SCREEN_H - 130, iD[3], iD[0], 0);
    PlaceSurface(SCREEN_W - 420, SCREEN_H - 125, tD[1], iD[0], 0);
    PlaceSurface(SCREEN_W - 435, SCREEN_H - 90,  iD[3], iD[0], 0);
    PlaceSurface(SCREEN_W - 430, SCREEN_H - 85,  tD[2], iD[0], 0);
    PlaceSurface(SCREEN_W - 435, SCREEN_H - 50,  iD[3], iD[0], 0);
    PlaceSurface(SCREEN_W - 365, SCREEN_H - 45,  tD[3], iD[0], 0);
}


void logicMainMenu(SDL_Event ev, GameState &state, bool &done, iArr iD, tArr tD)
{
    if (mouseOverArea(ev.motion.x, ev.motion.y, {MAIN_P1}))
    {
        if (ev.type == SDL_MOUSEBUTTONDOWN)
        {
            if (ev.button.button == SDL_BUTTON_LEFT)
            {
                state = ONE_PLAYER;
            }
        }
    }

    else if (mouseOverArea(ev.motion.x, ev.motion.y, {MAIN_P2}))
    {
        if (ev.type == SDL_MOUSEBUTTONDOWN)
        {
            if (ev.button.button == SDL_BUTTON_LEFT)
            {
                state = TWO_PLAYER;
            }
        }
    }

    else if (mouseOverArea(ev.motion.x, ev.motion.y, {MAIN_EXIT}))
    {
        if (ev.type == SDL_MOUSEBUTTONDOWN)
        {
            if (ev.button.button == SDL_BUTTON_LEFT)
            {
                done = true;
            }
        }
    }
}


void drawSPlayer(iArr& iD, const tArr& tD)
{
    // Clear the screen surface
    FillWholeRect(iD[0], {0, 0, 0});
    // Draw the game board
    PlaceSurface(0, 0, iD[1], iD[0], 0);

    PlaceSurface(iD[1] -> w + 65, iD[1] -> h - 355, tD[4],  iD[0], 0);
    PlaceSurface(iD[1] -> w + 65, iD[1] -> h - 305, tD[5],  iD[0], 0);
    PlaceSurface(iD[1] -> w + 80, iD[1] -> h - 250, tD[7],  iD[0], 0);
    PlaceSurface(iD[1] -> w + 10, iD[1] -> h - 150, iD[2],  iD[0], 0);
    PlaceSurface(iD[1] -> w + 60, iD[1] -> h - 140, tD[8],  iD[0], 0);
    PlaceSurface(iD[1] -> w + 10, iD[1] -> h - 100, iD[2],  iD[0], 0);
    PlaceSurface(iD[1] -> w + 65, iD[1] -> h - 90,  tD[10], iD[0], 0);
    PlaceSurface(iD[1] -> w + 10, iD[1] -> h - 50,  iD[2],  iD[0], 0);
    PlaceSurface(iD[1] -> w + 80, iD[1] -> h - 40,  tD[9],  iD[0], 0);
}


void logicSPlayer(SDL_Event ev, GameState &state, bool &done, iArr& iD, tArr tD, fArr& fD, Mark (&game_board)[ROWS][COLS], Mark& s_mark, GameStats& s)
{
    if (mouseOverArea(ev.motion.x, ev.motion.y, {BOARD}))
    {
        if (mouseOverArea(ev.motion.x, ev.motion.y, {BLOCK1}))
        {
            if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                if (ev.button.button == SDL_BUTTON_LEFT)
                {
                    if (!isEmpty(game_board, {0, 0}))
                        return;

                    PlaceSurface(40, 30, iD[4], iD[1], 0);
                    updateGameBoard(game_board, {0, 0}, s_mark);
                    s_mark = (s_mark == X_MARK) ? O_MARK : X_MARK;
                    std::swap(*iD[4], *iD[5]);
                }
            }
        }

        else if (mouseOverArea(ev.motion.x, ev.motion.y, {BLOCK2}))
        {
            if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                if (ev.button.button == SDL_BUTTON_LEFT)
                {
                    if (!isEmpty(game_board, {0, 1}))
                        return;

                    PlaceSurface(210, 30, iD[4], iD[1], 0);
                    updateGameBoard(game_board, {0, 1}, s_mark);
                    s_mark = (s_mark == X_MARK) ? O_MARK : X_MARK;
                    std::swap(*iD[4], *iD[5]);
                }
            }
        }

        else if (mouseOverArea(ev.motion.x, ev.motion.y, {BLOCK3}))
        {
            if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                if (ev.button.button == SDL_BUTTON_LEFT)
                {
                    if (!isEmpty(game_board, {0, 2}))
                        return;

                    PlaceSurface(380, 30, iD[4], iD[1], 0);
                    updateGameBoard(game_board, {0, 2}, s_mark);
                    s_mark = (s_mark == X_MARK) ? O_MARK : X_MARK;
                    std::swap(*iD[4], *iD[5]);
                }
            }
        }

        else if (mouseOverArea(ev.motion.x, ev.motion.y, {BLOCK4}))
        {
            if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                if (ev.button.button == SDL_BUTTON_LEFT)
                {
                    if (!isEmpty(game_board, {1, 0}))
                        return;

                    PlaceSurface(40, 150, iD[4], iD[1], 0);
                    updateGameBoard(game_board, {1, 0}, s_mark);
                    s_mark = (s_mark == X_MARK) ? O_MARK : X_MARK;
                    std::swap(*iD[4], *iD[5]);
                }
            }
        }

        else if (mouseOverArea(ev.motion.x, ev.motion.y, {BLOCK5}))
        {
            if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                if (ev.button.button == SDL_BUTTON_LEFT)
                {
                    if (!isEmpty(game_board, {1, 1}))
                        return;

                    PlaceSurface(210, 150, iD[4], iD[1], 0);
                    updateGameBoard(game_board, {1, 1}, s_mark);
                    s_mark = (s_mark == X_MARK) ? O_MARK : X_MARK;
                    std::swap(*iD[4], *iD[5]);
                }
            }
        }

        else if (mouseOverArea(ev.motion.x, ev.motion.y, {BLOCK6}))
        {
            if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                if (ev.button.button == SDL_BUTTON_LEFT)
                {
                    if (!isEmpty(game_board, {1, 2}))
                        return;

                    PlaceSurface(380, 150, iD[4], iD[1], 0);
                    updateGameBoard(game_board, {1, 2}, s_mark);
                    s_mark = (s_mark == X_MARK) ? O_MARK : X_MARK;
                    std::swap(*iD[4], *iD[5]);
                }
            }
        }

        else if (mouseOverArea(ev.motion.x, ev.motion.y, {BLOCK7}))
        {
            if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                if (ev.button.button == SDL_BUTTON_LEFT)
                {
                    if (!isEmpty(game_board, {2, 0}))
                        return;

                    PlaceSurface(40, 270, iD[4], iD[1], 0);
                    updateGameBoard(game_board, {2, 0}, s_mark);
                    s_mark = (s_mark == X_MARK) ? O_MARK : X_MARK;
                    std::swap(*iD[4], *iD[5]);
                }
            }
        }

        else if (mouseOverArea(ev.motion.x, ev.motion.y, {BLOCK8}))
        {
            if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                if (ev.button.button == SDL_BUTTON_LEFT)
                {
                    if (!isEmpty(game_board, {2, 1}))
                        return;

                    PlaceSurface(210, 270, iD[4], iD[1], 0);
                    updateGameBoard(game_board, {2, 1}, s_mark);
                    s_mark = (s_mark == X_MARK) ? O_MARK : X_MARK;
                    std::swap(*iD[4], *iD[5]);
                }
            }
        }

        else if (mouseOverArea(ev.motion.x, ev.motion.y, {BLOCK9}))
        {
            if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                if (ev.button.button == SDL_BUTTON_LEFT)
                {
                    if (!isEmpty(game_board, {2, 2}))
                        return;

                    PlaceSurface(380, 270, iD[4], iD[1], 0);
                    updateGameBoard(game_board, {2, 2}, s_mark);
                    s_mark = (s_mark == X_MARK) ? O_MARK : X_MARK;
                    std::swap(*iD[4], *iD[5]);
                }
            }
        }
    }

        else if (mouseOverArea(ev.motion.x, ev.motion.y, {TO_MAIN}))
        {
            if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                if (ev.button.button == SDL_BUTTON_LEFT)
                {
                    FillWholeRect(iD[0], {0x00, 0x00, 0x00});
                    PlaceSurface(0, 0, iD[6], iD[1], 0);
                    initGameBoard(game_board);
                    s.clearStats();
                    state = MAIN_MENU;
                }
            }
        }

        else if (mouseOverArea(ev.motion.x, ev.motion.y, {RESTART}))
        {
            if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                if (ev.button.button == SDL_BUTTON_LEFT)
                {
                    initGameBoard(game_board);
                    PlaceSurface(0, 0, iD[6], iD[1], 0);
                }
            }
        }

        else if (mouseOverArea(ev.motion.x, ev.motion.y, {QUIT}))
        {
            if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                if (ev.button.button == SDL_BUTTON_LEFT)
                {
                    done = true;
                }
            }
        }
}


void drawMPlayer(const iArr &iD, const tArr &tD)
{
    PlaceSurface(iD[1] -> w + 65, iD[1] -> h - 355, tD[4],  iD[0], 0);
    PlaceSurface(iD[1] -> w + 65, iD[1] -> h - 305, tD[6],  iD[0], 0);
    PlaceSurface(iD[1] -> w + 80, iD[1] -> h - 250, tD[7],  iD[0], 0);
    PlaceSurface(iD[1] -> w + 10, iD[1] -> h - 150, iD[2],  iD[0], 0);
    PlaceSurface(iD[1] -> w + 60, iD[1] -> h - 140, tD[8],  iD[0], 0);
    PlaceSurface(iD[1] -> w + 10, iD[1] -> h - 100, iD[2],  iD[0], 0);
    PlaceSurface(iD[1] -> w + 65, iD[1] -> h - 90,  tD[10], iD[0], 0);
    PlaceSurface(iD[1] -> w + 10, iD[1] -> h - 50,  iD[2],  iD[0], 0);
    PlaceSurface(iD[1] -> w + 80, iD[1] -> h - 40,  tD[9],  iD[0], 0);
}


void logicMPlayer(SDL_Event ev, GameState &state, bool &done, iArr iD, tArr tD, Mark (&game_board)[ROWS][COLS])
{
    if (mouseOverArea(ev.motion.x, ev.motion.y, {TO_MAIN}))
    {
        if (ev.type == SDL_MOUSEBUTTONDOWN)
        {
            if (ev.button.button == SDL_BUTTON_LEFT)
            {
                initGameBoard(game_board);
                FillWholeRect(iD[0], {0x00, 0x00, 0x00});
                drawMainMenu(iD, tD);
                state = MAIN_MENU;
            }
        }
    }

    else if (mouseOverArea(ev.motion.x, ev.motion.y, {RESTART}))
    {
        if (ev.type == SDL_MOUSEBUTTONDOWN)
        {
            if (ev.button.button == SDL_BUTTON_LEFT)
            {
                initGameBoard(game_board);
                PlaceSurface(0, 0, iD[1], iD[0], 0);
            }
        }
    }

    else if (mouseOverArea(ev.motion.x, ev.motion.y, {QUIT}))
    {
        if (ev.type == SDL_MOUSEBUTTONDOWN)
        {
            if (ev.button.button == SDL_BUTTON_LEFT)
            {
                done = true;
            }
        }
    }
}


int main(int argc, char *args[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        atexit(SDL_Quit);
    }

    if (TTF_Init() == -1)
    {
        printf("TTF_Init failed: %s\n", TTF_GetError());
        return -1;
    }

    SDL_WM_SetCaption("Tic-Tac-Toe v1.0", nullptr);

    iArr image_data;

    initDisplay(image_data);

    initImageData(image_data);

    fArr font_data;

    initFontData(font_data);

    tArr text_data;

    initStringData(text_data, font_data);

    GameStats stats;
    // Game board conceptual representation
    Mark game_board[ROWS][COLS];
    // Every board block is initialized to EMPTY
    initGameBoard(game_board);
    // The starting mark
    Mark s_mark = X_MARK;
    // SDL_Event handler
    SDL_Event ev;
    // The starting/current game mode
    GameState curr_game_state = MAIN_MENU;
    // Are we done playing?
    bool done = false;

    while (!done)
    {
        while (SDL_PollEvent(&ev))
        {
            switch (curr_game_state)
            {
                case (MAIN_MENU):
                    logicMainMenu(ev, curr_game_state, done, image_data, text_data);
                    break;

                case (ONE_PLAYER):
                    logicSPlayer(ev, curr_game_state, done, image_data, text_data, font_data, game_board, s_mark, stats);
                    break;

                case (TWO_PLAYER):
                    logicMPlayer(ev, curr_game_state, done, image_data, text_data, game_board);
                    break;

                default:
                    break;
            }

            if (ev.type == SDL_QUIT)
                done = true;
        }

        switch (curr_game_state)
        {
            case (MAIN_MENU):
                drawMainMenu(image_data, text_data);
                break;

            case (ONE_PLAYER):
                drawSPlayer(image_data, text_data);
                drawGameStats(stats, image_data, text_data, font_data);
                //updateGameStats(game_board, stats);
                break;

            case (TWO_PLAYER):
                drawMPlayer(image_data, text_data);
                break;

            default:
                break;
        }

        SDL_Flip(image_data[0]);
    }

    cleanUp(image_data, font_data, text_data);

    TTF_Quit();

    atexit(SDL_Quit);

    return 0;
}
