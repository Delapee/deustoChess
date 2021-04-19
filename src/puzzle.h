#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include <stdio.h>

#define TXT "../../../data/puzzles/puzzles.txt"

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
void playPuzzle(Puzzle** puzzles, int pSize);
void result(int pSize, int pPosition, int pass, int fail, int lifes);
int loadPuzzle(Puzzle* puzzle);
Puzzle* nextPuzzle(Puzzle** puzzles, int* pPosition);
int checkMovement(char* playerMove, char* rigthMove);
void randomPuzzles(Puzzle** puzzles, int size);

#endif