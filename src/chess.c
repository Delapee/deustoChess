#include <stdio.h>
#include <string.h>
#include "chess.h"

void test(void)
{
    Board bo;
    Board *bi = &bo;
    char jugada[5];
    prepareBoard(bi);
    do {
        printBoard(bi, 0);
        printf("\n\nSeleccione una jugada: ");
        gets_s(jugada, 5);
        if (isMove(bi, jugada)) movePiece(bi, jugada);
        checkCastle(bi);

        system("cls");

    } while (jugada[0] != 'i');

}

// Metodos tablero

void prepareBoard(Board* bo) {
    bo->turn = 0;

    for (size_t i = 0; i < 64; i++)
    {
        bo->panel[i][0] = ' ';
        bo->panel[i][1] = ' ';
        bo->panel[i][2] = '\0';
    }

    bo->castl[0] = 1;
    bo->castl[1] = 1;
    bo->castl[2] = 1;
    bo->castl[3] = 1;

    loadPanel(bo, "e1/d1/a1h1/c1XX/b1XX/a2b2c2d2e2f2g2h2|e8/d8/a8h8/c8f8/b8g8/a7b7c7d7e7f7g7h7", 1);
}


void loadPanel(Board *bo, char status[80], int i)
{
    char white[40];
    char black[40];
    char *token = strtok(status, "|");
    strcpy(white, token);
    token = strtok(NULL, "|");
    strcpy(black, token);

    loadPiece(bo, white, 'b');
    loadPiece(bo, black, 'n');
}

void loadPiece(Board *bo, char status[40], char player)
{
    char piece[6] = { 'R','D','T','A','C','P' };
    int lo[6] = { 1, 1, 2, 2, 2, 8 };
    char *token = strtok(status, "/");
    for (size_t i = 0; i < 6; i++)
    {   
        for (int j = 0; j < lo[i]*2; j+=2)
        {   
            char pos[3] = { token[j], token[j+1], '\0' };
            char pieceT[3] = { piece[i], player , '\0'};
            if (getPiece(bo, pos) != 'X') {
                strcpy(bo->panel[getPos(pos)], pieceT);
            }
            
            
        }
        token = strtok(NULL, "/");
    }

}

void printBoard(Board *bo, int player)
{   
    printf("\n");
    char s = 'a';
    int t = 1;
    for (int i = 56; i >= 0; i -= 8)
    {
        if (player == 0)
        {
            printf("\t%d\t|", (i / 8) + 1);
            for (size_t j = 0; j < 8; j++)
            {
                printf("   %s   |", bo->panel[i + j]);
            }
        }
        else
        {
            printf("\t%d\t|", 8 - (i / 8) );
            s = 'h';
            t = -1;
            for (int j = 7; j >= 0; j--)
            {
                printf("   %s   |", bo->panel[(56-i) + j]);
            }
        }
        printf("\n");
    }

    printf("\n\t\t");
    for (size_t i = 0; i < 8; i++)
    {
        printf("    %c    ", i*t + s);
    }
}

// Utilidades
int getPos(char move[3]) 
{
    int base = move[0] - 'a';
    return base + 8 * (move[1] - '1');
}

char getColumn(char move[3])
{
    return move[0];
}

int getRow(char move[3])
{
    return move[1] - '0';
}

char getPiece(Board *bo, char move[3])
{
    return bo->panel[getPos(move)][0];
}

char getColor(Board *bo, char move[3])
{
    return bo->panel[getPos(move)][1];
}

int isBlock(Board *bo, char start[3], char end[3]) {
    int s, e;
    int t1, t2;

    if (getColumn(start) == getColumn(end)) {
        if (getRow(start) < getRow(end)) {
            s = getRow(start);
            e = getRow(end);
            t1 = 1;
        }
        else
        {
            s = getRow(end) + 1;
            e = getRow(start);
            t1 = -1;
        }

        for (int i = 1; i < e - s; i++)
        {
            char pos[3] = { getColumn(start), (getRow(start) + i*t1) + '0', '\n' };
            if (getColor(bo, pos) != ' ')
            {
                return 1;
            }
        }
        return 0;
    }
    else if (getRow(start) == getRow(end))
    {
        if (getColumn(start) < getColumn(end)) {
            s = getColumn(start) - 'a';
            e = getColumn(end) - 'a';
            t1 = 1;
        }
        else
        {
            s = getColumn(end) - 'a';
            e = getColumn(start) - 'a';
            t1 = -1;
        }

        for (int i = 1; i < e - s; i++)
        {
            char pos[3] = { getColumn(start) + i*t1, getRow(start) + '0', '\n' };
            if (getColor(bo, pos) != ' ')
            {
                return 1;
            }
        }

        return 0;
    }
    else if (abs(getRow(start) - getRow(end)) == abs(getColumn(start) - getColumn(end)))
    {
        if (getRow(start) - getRow(end) > 0 && getColumn(start) - getColumn(end) > 0 ) {        // ++
            s = getColumn(start);
            e = getColumn(end);
            t1 = -1;
            t2 = -1;
        }
        else if (getRow(start) - getRow(end) < 0 && getColumn(start) - getColumn(end) < 0)      // --
        {
            s = getColumn(end);
            e = getColumn(start);
            t1 = 1;
            t2 = 1;
        }
        else if (getRow(start) - getRow(end) < 0 && getColumn(start) - getColumn(end) > 0)      // -+
        {
            s = getColumn(start);
            e = getColumn(end);
            t1 = -1;
            t2 = 1;
        }
        else if (getRow(start) - getRow(end) > 0 && getColumn(start) - getColumn(end) < 0)      // +-
        {
            s = getColumn(start);
            e = getColumn(end);
            t1 = -1;
            t2 = 1;
        }


        for (int i = 1; i < s - e; i++)
        {
            char pos[3] = { getColumn(start) + i * t1, (getRow(start) + i * t2 ) + '0', '\n' };
            if (getColor(bo, pos) != ' ')
            {
                return 1;
            }
        }

        return 0;

    }

    return 1;
    
}

// Movimento
void movePiece(Board *bo, char move[5])
{
    char start[3] = { move[0], move[1], '\0' };
    char end[3] = { move[2], move[3], '\0'};

    strcpy(bo->panel[getPos(end)], bo->panel[getPos(start)]);
    strcpy(bo->panel[getPos(start)], "  ");
        
}

int isMove(Board *bo, char move[5])
{

    char start[3] = { move[0], move[1], '\0' };
    char end[3] = { move[2], move[3], '\0' };
    char pieceS[3] = { getPiece(bo, start), getColor(bo, start), '\0' };
    char pieceE[3] = { getPiece(bo, end), getColor(bo, end) , '\0' };
    int t = (pieceS[1] == 'b') ? 1 : -1;
    
    if (pieceS[1] != pieceE[1])     // La pieza es de distinto color
    {
        if (pieceE[0] != 'R')       // La pieza no es un rey
        {
            switch (pieceS[0])
            {
            case 'P':         

                if (getPos(start) + 8 * t == getPos(end) && getPiece(bo, end) == ' ')  // Mover normal
                {
                    return 1;
                }
                else if ( (getPos(start) + 7 * t == getPos(end) || getPos(start) + 9 * t == getPos(end)) && pieceE[0] != ' ') //Comer
                {
                    return 1;
                }               
                else if (getPos(start) + 16 * t == getPos(end) && isBlock(bo, start, end) == 0 && getPiece(bo, end) == ' ')  // Avanzar 2 casillas 
                {
                    if ( (t == 1 && getRow(start) == 2) || (t == -1 && getRow(start) == 7))
                    {
                        return 1;
                    }
                }
    
                break;
            
            case 'C':

                if (getColumn(start) != 'a') 
                {  
                    if (getPos(start) + 15 == getPos(end) && getRow(start) < 7)        
                    {
                        return 1;
                    }
                    else if (getPos(start) - 17 == getPos(end) && getRow(start) > 2)        
                    {
                        return 1;
                    }
                    else if (getColumn(start) != 'b')
                    {
                        if (getPos(start) + 6 == getPos(end) && getRow(start) != 8)        
                        {
                            return 1;
                        }
                        else if (getPos(start) - 10 == getPos(end) && getRow(start) != 1)   
                        {
                            return 1;
                        }
                    }
                }

                if (getColumn(start) != 'h')
                {
                    if (getPos(start) + 17 == getPos(end) && getRow(start) < 7)        
                    {
                        return 1;
                    }
                    else if (getPos(start) - 15 == getPos(end) && getRow(start) > 2)        
                    {
                        return 1;
                    }
                    else if (getColumn(start) != 'g')
                    {
                        if (getPos(start) + 10 == getPos(end) && getRow(start) != 8)         
                        {
                            return 1;
                        }
                        else if (getPos(start) - 6 == getPos(end) && getRow(start) != 1)  
                        {
                            return 1;
                        }
                    }
                }

                break;

            case 'A':

                if (getColumn(start) != getColumn(end) && getRow(start) != getRow(end) && isBlock(bo, start, end) == 0)
                {
                    return 1;
                }

                break;

            case 'T':

                if (getColumn(start) == getColumn(end) && isBlock(bo, start, end) == 0)
                {
                    return 1;
                }
                else if (getRow(start) == getRow(end) && isBlock(bo, start, end) == 0)
                {
                    return 1;
                }

                break;

            case 'D':

                if (getColumn(start) == getColumn(end) && isBlock(bo, start, end) == 0)
                {
                    return 1;
                }
                else if (getRow(start) == getRow(end) && isBlock(bo, start, end) == 0)
                {
                    return 1;
                }
                if (getColumn(start) != getColumn(end) && getRow(start) != getRow(end) && isBlock(bo, start, end) == 0)
                {
                    return 1;
                }
                break;
            case 'R':
                
                if ((getPos(start) - 1 == getPos(end) || getPos(start) + 7 == getPos(end)       // Movimiento lateral izquierdo
                    || getPos(start) - 9 == getPos(end)) && (getColumn(start) != 'a'))
                {
                    return 1;
                }
                else if ((getPos(start) + 1 == getPos(end) || getPos(start) + 9 == getPos(end)  // Movimiento lateral derecho
                    || getPos(start) - 7 == getPos(end)) && (getColumn(start) != 'h'))
                {
                    return 1;
                }
                else if (getPos(start) + 8 == getPos(end) || getPos(start) - 8 == getPos(end))  // Movimiento Frontal
                {
                    return 1;
                }
                else if (getColor(bo, start) == 'b') 
                {
                    if (getPos(start) + 2 == getPos(end) && bo->castl[1] == 1 && isBlock(bo, "e1", "h1") == 0)
                    {
                        movePiece(bo, "h1f1\0");
                        return 1;
                    }
                    else if (getPos(start) - 2 == getPos(end) && bo->castl[0] == 1 && isBlock(bo, "e1", "a1") == 0)
                    {
                        movePiece(bo, "a1d1\0");
                        return 1;
                    }
                }
                else
                {
                    if (getPos(start) + 2 == getPos(end) && bo->castl[3] == 1 && isBlock(bo, "e8", "h8") == 0)
                    {
                        //move(bo, "h8f8\0");
                        return 1;
                    }
                    else if (getPos(start) - 2 == getPos(end) && bo->castl[3] == 1 && isBlock(bo, "e8", "a8") == 0)
                    {
                        //move(bo, "a8d8\0");
                        return 1;
                    }
                }
                break;

            default:
                break;
            }
        }
    }
    
    printf("\nMovimiento no valido");
    return 0;
}

void checkCastle(Board *bo)
{
 
    if (bo->panel[getPos("e8") != "Rb"] && (bo->castl[2] == 1 || bo->castl[3] == 1))
    {
        bo->castl[0] = 0;
        bo->castl[1] = 0;
    }
    else if (bo->panel[getPos("a1") != "Tb"] && bo->castl[0] == 1)
    {
        bo->castl[0] = 0;
    }
    else if (bo->panel[getPos("h1") != "Tb"] && bo->castl[1] == 1)
    {
        bo->castl[1] = 0;
    }
    
    if (bo->panel[getPos("e8") != "Rn"] && (bo->castl[2] == 1 || bo->castl[3] == 1))
    {
        bo->castl[2] = 0;
        bo->castl[3] = 0;
    }
    
    else if (bo->panel[getPos("a8") != "Tn"] && bo->castl[2] == 1)
    {
        bo->castl[2] = 0;
    }
    else if (bo->panel[getPos("h8") != "Tn"] && bo->castl[3] == 1)
    {
        bo->castl[3] = 0;
    }

}