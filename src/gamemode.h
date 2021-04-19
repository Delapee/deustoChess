#ifndef _GAMEMODE_
#define _GAMEMODE_

#include "chess.h"

void offlineGamemode(void);
void initPuzzles(void);

void initGame(Board* bo);
int makeMove(Board* bo, char player);
void checkAll(Board* bo);
char rPlayer(char player);

#endif