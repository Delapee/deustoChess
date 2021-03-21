#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include <stdio.h>

typedef struct Puzzle
{
	int movements;
	int player;
	char initialState[80];
	char movementStates[16][4];
	int mState;
} Puzzle;

void initPuzzles(void);
void readPuzzle(FILE *f, Puzzle** puzzles);
int nRow(FILE* f);
void loadPuzzle(Puzzle* puzzle);
Puzzle* nextPuzzle(Puzzle** puzzles, int* pPosition);
//Puzzle** randomPuzzles(Puzzle** puzzles, int size);
int checkMovement(char* playerMove, char* rigthMove);

#endif