#include <stdio.h>
#include <string.h>
#include "chess.h"
#include "gamemode.h"

// Modos de Juego
void offlineGamemode() 
{
	Board bo;
	initGame(&bo);
	char player = 'b';

	while (isCheck(&bo, 'n') != 2 && isCheck(&bo, 'b') != 2)
	{
		if (makeMove(&bo, player) == 1) {
			player = rPlayer(player);
			break;
		}
		player = rPlayer(player);
		checkAll(&bo);
	}
	system("cls");
	(player == 'b') ? printf("Ha ganado el jugador Blanco") : printf("Ha ganado el jugador Negro");
}


// Modos de Juego
void initGame(Board* bo) 
{
	prepareBoard(bo);
	loadPanel(bo, sPos);;
}

int makeMove(Board* bo, char player) 
{
	int submit = 1;
	char mo[5];
	do
	{
		system("cls");
		printBoard(bo, (player == 'b') ? 0 : 1);
		printf("\n\n\n\t");
		(player == 'b') ? printf("Mueven Blancas") : printf("Mueven Negras");
		printf("\n\tCasilla Inicio + fin Ej -> e2e4");
		printf("\n\tFF Para rendirse");
		printf("\n\n\tSeleccione una jugada: ");
		scanf("%s", &mo);
		char piece[2] = { mo[0] , mo[1] };
		if (mo[0] == 'F' && mo[1] == 'F')
		{
			return 1;
		}
		else if (getColor(bo,piece) == player && isMove(bo, mo, 0) && isNailed(bo, mo) == 0) {
			movePiece(bo, mo);
			return 0;
		}
		
	} while (1);
}

void checkAll(Board* bo) {
	checkCastle(bo);
	isPromote(bo);
}

char rPlayer(char player) {
	if (player == 'b') player = 'n';
	else player = 'b';
	return player;
}