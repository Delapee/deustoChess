#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "puzzle.h"
#include "chess.h"


#define TXT "..\\..\\..\\..\\data\\puzzles.txt"


void initPuzzles()
{
	FILE* f;

	f = fopen(TXT, "r");

	if (f == NULL) {
		printf("\nERROR!! No se puede abrir el archivo\n");
	}
	else 
	{
		int pPosition = 0;
		int pSize = nRow(f);
		Puzzle** puzzles = (Puzzle**)malloc(pSize * sizeof(Puzzle*));

		rewind(f);
		readPuzzle(f, puzzles);
		fclose(f);

		loadPuzzle(nextPuzzle(puzzles, &pPosition));
		
	}
}

void readPuzzle(FILE* f, Puzzle** puzzles)
{
	char c;
	char buff[1000];
	int i = 0;
	int j = 0;
	
	do {
		do
		{ 
			c = fgetc(f);
			buff[i] = c;
			i++;
		} while (c != '\n' && c != EOF);
		buff[i] = '\0';

		Puzzle* puzz = (Puzzle*)malloc(sizeof(Puzzle));
		puzz->mState = 0;
		char* token = strtok(buff, "@");
		puzz->movements = atoi(token);
		token = strtok(NULL, "@");
		if (token[0] == 'B')
		{
			puzz->player = 0;
		}
		else
		{
			puzz->player = 1;
		}
		token = strtok(NULL, "@");
		strcpy(puzz->initialState, token);
		int k;
		for ( k = 0; k < puzz->movements; k++)
		{
			token = strtok(NULL, "@");
			strcpy(puzz->movementStates[k], token);
		}
		puzzles[j] = puzz;
		j++;

		memset(buff, 0, 1000);
		i = 0;
	} while (c != EOF);
}

int nRow(FILE* f)
{
	int maxr = 1;
	char c;
	do {
		c = fgetc(f);
		if (c == '\n') maxr++;
	} while (c != EOF);

	return maxr;
}

void loadPuzzle(Puzzle* puzzle)
{
	Board bo;
	Board* bi = &bo;
	char jugada[5];
	prepareBoard(bi);
	
	loadPanel(&bo, puzzle->initialState);
	//printBoard(bi, 1);
	do {
		printBoard(bi, 1);
		printf("\n\nSeleccione una jugada: ");
		gets_s(jugada, 5);

		if (isMove(bi, jugada, 0))
		{
			if (checkMovement(jugada, puzzle->movementStates[puzzle->mState])) 
			{
				movePiece(bi, jugada);
				if (puzzle->mState < puzzle->movements-1)
				{
					system("cls");
					printBoard(bi, 1);
					Sleep(800);
					puzzle->mState++;
					movePiece(bi, puzzle->movementStates[puzzle->mState]);
					puzzle->mState++;
				}
				else if(puzzle->mState == puzzle->movements - 1)
				{
					// Tengo que pensar
				}
				
			}
			else
			{
				// Tengo que pensar
			}
		}

		system("cls");
	} while (jugada[0] != 'i');
}

Puzzle* nextPuzzle(Puzzle** puzzles, int* pPosition)
{
	*pPosition = *pPosition + 1;
	return puzzles[*pPosition];
}

int checkMovement(char* playerMove, char* rigthMove)
{
	int i;
	for ( i = 0; i < 4; i++)
	{
		if (playerMove[i] != rigthMove[i]) return 0;
	}

	return 1;
}