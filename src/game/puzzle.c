#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "puzzle.h"
#include "chess.h"

typedef enum { false, true } bool;


void initPuzzles()
{
	FILE* f;

	f = fopen(TXT, "r");

	if (f == NULL) {
		printf("\nERROR!! No se puede abrir el archivo\n");
	}
	else
	{
		int pSize = nRow(f);
		Puzzle** puzzles = (Puzzle**)malloc(pSize * sizeof(Puzzle*));

		rewind(f);
		readPuzzle(f, puzzles);
		fclose(f);

		randomPuzzles(puzzles, pSize);
		playPuzzle(puzzles, pSize);

		int i;
		for (i = 0; i < pSize; i++)
		{
			free(puzzles[i]);
			puzzles[i] = NULL;
		}
		free(puzzles);
		puzzles = NULL;
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

void playPuzzle(Puzzle** puzzles, int pSize)
{
	int puzzleResult;
	int pPosition = -1;
	int lifes = 3;
	int pass = 0;
	int fail = 0;
	bool next = true;
	do
	{
		if (pPosition != -1)
		{
			printf("\nLLevas acertados %d de %d puzzles", pass, pPosition + 1);
			Sleep(1800);
			system("cls");
		}
		puzzleResult = loadPuzzle(nextPuzzle(puzzles, &pPosition));
		if (puzzleResult == 1)
		{
			pass++;
			printf("\nFelicidades has resuelto el problema");
			printf("\n\nVidas %d de 3", lifes);
			Sleep(1500);
		}
		else
		{
			fail++;
			lifes--;
			printf("\nHas fallado");
			printf("\n\nVidas %d de 3", lifes);
			Sleep(1500);
		}

		if (pPosition + 1 >= pSize || lifes == 0)
		{
			result(pSize, pPosition, pass, fail, lifes);
			next = false;
		}

		system("cls");
	} while (next);
}

void result(int pSize, int pPosition, int pass, int fail, int lifes)
{
	system("cls");
	if (lifes > 0) printf("\nFelicidades has terminado de resolver los puzzles\n");
	printf("\n- Puzzles totales: %d\n", pSize);
	printf("- Puzzles jugados: %d\n", pPosition + 1);
	printf("\t- Resueltos: %d\n", pass);
	printf("\t- Resueltos: %d\n", fail);
	Sleep(3000);
}

int loadPuzzle(Puzzle* puzzle)
{
	Board bo;
	Board* bi = &bo;
	char jugada[5];
	bool rigth = true;
	prepareBoard(bi);
	
	loadPanel(&bo, puzzle->initialState);
	do {
		printBoard(bi, 1);
		if (puzzle->player == 0) printf("\n\nMueven blancas");
		else printf("\n\nMueven Negras");
		printf("\nSeleccione una jugada: ");
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
					Sleep(1200);
					puzzle->mState++;
					movePiece(bi, puzzle->movementStates[puzzle->mState]);
					puzzle->mState++;
				}
				else if(puzzle->mState == puzzle->movements - 1)
				{
					system("cls");
					printBoard(bi, 1);
					Sleep(800);
					return 1;
				}
			}
			else
			{
				rigth = false;
			}
		}

		system("cls");
	} while (rigth);

	return 0;
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

void randomPuzzles(Puzzle** puzzles, int size)
{
	srand(time(NULL));
	int i;
	for (i = 0; i < size - 1; i++)
	{
		int j = i + rand() / (RAND_MAX / (size - i) + 1);
		Puzzle* p = puzzles[j];
		puzzles[j] = puzzles[i];
		puzzles[i] = p;
	}
}