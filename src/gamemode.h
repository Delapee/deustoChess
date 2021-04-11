#ifndef _GAMEMODE_
#define _GAMEMODE_

void offlineGamemode(void);
void initGame(Board* bo);
int makeMove(Board* bo, char player);
void checkAll(Board* bo);
char rPlayer(char player);

#endif