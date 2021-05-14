#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include "chess.h"

// Metodos tablero
void clearPanel(Board* bo)
{
    for (size_t i = 0; i < 64; i++)
    {
        bo->panel[i][0] = ' ';
        bo->panel[i][1] = ' ';
        bo->panel[i][2] = '\0';
    }
}

void prepareBoard(Board* bo)
{
    clearPanel(bo);
    bo->castl[0] = 1;
    bo->castl[1] = 1;
    bo->castl[2] = 1;
    bo->castl[3] = 1;
}

void loadPanel(Board* bo, char status[80])
{
    clearPanel(bo);
    char nStatus[80];
    char white[40];
    char black[40];

    strcpy(nStatus, status);
    char* token = strtok(nStatus, "|");
    strcpy(white, token);
    token = strtok(NULL, "|");
    strcpy(black, token);

    loadPiece(bo, white, 'b');
    loadPiece(bo, black, 'n');
}

void loadPiece(Board* bo, char status[40], char player)
{
    char piece[6] = { 'R','D','T','A','C','P' };

    int j = 0;
    for (size_t i = 0; i < 6; i++)
    {
        while (status[j] != '/')
        {
            char pos[3] = { status[j], status[j + 1], '\0' };
            char pieceT[3] = { piece[i], player , '\0' };
            strcpy(bo->panel[getPos(pos)], pieceT);
            j += 2;
        }
        j++;
    }
}

void savePanel(Board* bo, char status[80]) 
{

    char piece[6] = { 'R','D','T','A','C','P' };
    char wResult[80] = "";
    char bResult[80] = "";

    for (size_t i = 0; i < 6; i++)
    {
        for (size_t j = 0; j < 64; j++)
        {
            if (bo->panel[j][0] == piece[i]) {
                char pos[3] = { getColumnId(j) ,getRowId(j) + '0', '\0' };
                if (bo->panel[j][1] == 'b')
                {
                    strcat(wResult, pos);
                }
                else if (bo->panel[j][1] == 'n')
                {
                    strcat(bResult, pos);
                }
            }
        }
        strcat(wResult, "/\0");
        strcat(bResult, "/\0");
    }
    strcat(wResult, "|\0");
    strcat(wResult, bResult);
    strcpy(status, wResult);
}

void printBoard(Board* bo, int player)
{
    printf("\n\n");
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
            printf("\t%d\t|", 8 - (i / 8));
            s = 'h';
            t = -1;
            for (int j = 7; j >= 0; j--)
            {
                printf("   %s   |", bo->panel[(56 - i) + j]);
            }
        }
        printf("\n");
    }

    printf("\n\t\t");
    for (size_t i = 0; i < 8; i++)
    {
        printf("    %c    ", i * t + s);
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

char getPiece(Board* bo, char move[3])
{
    return bo->panel[getPos(move)][0];
}

char getColor(Board* bo, char move[3])
{
    return bo->panel[getPos(move)][1];
}

char getColumnId(int pos)
{
    char l[8] = { 'a','b','c','d','e','f','g','h' };

    while (pos > 7)
    {
        pos -= 8;
    }

    return l[pos];
}

int getRowId(int pos)
{
    int cont = 1;
    while (pos > 7)
    {
        pos -= 8;
        cont++;
    }

    return cont;
}

void setPiece(Board* bo, char comand[5]) {
    char pos[3] = { comand[2],comand[3],'\0' };
    bo->panel[getPos(pos)][0] = comand[0];
    bo->panel[getPos(pos)][1] = comand[1];
}

int isBlock(Board* bo, char start[3], char end[3]) {
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
            char pos[3] = { getColumn(start), (getRow(start) + i * t1) + '0', '\n' };
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
            char pos[3] = { getColumn(start) + i * t1, getRow(start) + '0', '\n' };
            if (getColor(bo, pos) != ' ')
            {
                return 1;
            }
        }

        return 0;
    }
    else if (abs(getRow(start) - getRow(end)) == abs(getColumn(start) - getColumn(end)))
    {
        if (getRow(start) - getRow(end) > 0 && getColumn(start) - getColumn(end) > 0) {        // ++
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
            s = getColumn(end);
            e = getColumn(start);
            t1 = 1;
            t2 = -1;
        }


        for (int i = 1; i < s - e; i++)
        {
            char pos[3] = { getColumn(start) + i * t1, (getRow(start) + i * t2) + '0', '\n' };
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
void movePiece(Board* bo, char move[5])
{
    char start[3] = { move[0], move[1], '\0' };
    char end[3] = { move[2], move[3], '\0' };

    strcpy(bo->panel[getPos(end)], bo->panel[getPos(start)]);
    strcpy(bo->panel[getPos(start)], "  ");

}

int isMove(Board* bo, char move[5], int protec)
{
    char start[3] = { move[0], move[1], '\0' };
    char end[3] = { move[2], move[3], '\0' };
    char pieceS[3] = { getPiece(bo, start), getColor(bo, start), '\0' };
    char pieceE[3] = { getPiece(bo, end), getColor(bo, end) , '\0' };
    int t = (pieceS[1] == 'b') ? 1 : -1;

    if ((pieceS[1] != pieceE[1] && end[1] - '0' < 9 && end[1] - '0' > 0) || protec == 1)     // La pieza es de distinto color
    {
        switch (pieceS[0])
        {
        case 'P':

            if (getPos(start) + 8 * t == getPos(end) && getPiece(bo, end) == ' ' && protec != 1)  // Mover normal
            {
                return 1;
            }
            else if (((getPos(start) + 7 * t == getPos(end) || getPos(start) + 9 * t == getPos(end)) && pieceE[1] != ' ')
                || protec && ((getPos(start) + 7 * t == getPos(end) || getPos(start) + 9 * t == getPos(end)) && pieceE[1] == ' '))  //Comer
            {
                if (pieceE[0] == ' ') {
                    bo->panel[getPos(end) - 8 * t][0] = ' ';
                    bo->panel[getPos(end) - 8 * t][1] = ' ';
                }
                return 1;
            }
            else if ((getPos(start) + 16 * t == getPos(end) && bo->panel[getPos(start) + 8 * t][0] == ' ' && getPiece(bo, end) == ' ') && protec != 1)  // Avanzar 2 casillas 
            {
                if ((t == 1 && getRow(start) == 2) || (t == -1 && getRow(start) == 7))
                {
                    bo->panel[getPos(end) - 8 * t][0] = 'W';
                    (t == 1) ? bo->panel[getPos(end) - 8 * t][1] = 'b': bo->panel[getPos(end) - 8 * t][1] = 'n';
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
            if (isSpot(bo, end, (pieceS[1] == 'b') ? 'n' : 'b') == 0)
            {
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
                    if (getPos(start) + 2 == getPos(end) && bo->castl[1] == 1 && isBlock(bo, "e1", "h1") == 0
                        && isSpot(bo, "f1\0", 'n') == 0 && isSpot(bo, "g1\0", 'n') == 0)
                    {
                        movePiece(bo, "h1f1\0");
                        return 1;
                    }
                    else if (getPos(start) - 2 == getPos(end) && bo->castl[0] == 1 && isBlock(bo, "e1", "a1") == 0
                        && isSpot(bo, "c1\0", 'n') == 0 && isSpot(bo, "d1\0", 'n') == 0)
                    {
                        movePiece(bo, "a1d1\0");
                        return 1;
                    }
                }
                else
                {
                    if (getPos(start) + 2 == getPos(end) && bo->castl[3] == 1 && isBlock(bo, "e8", "h8") == 0
                            && isSpot(bo, "f8\0", 'b') == 0 && isSpot(bo, "g8\0", 'b') == 0)
                    {
                        movePiece(bo, "h8f8\0");
                        return 1;
                    }
                    else if (getPos(start) - 2 == getPos(end) && bo->castl[2] == 1 && isBlock(bo, "e8", "a8") == 0
                        && isSpot(bo, "c8\0", 'b') == 0 && isSpot(bo, "d8\0", 'b') == 0)
                    {
                        movePiece(bo, "a8d8\0");
                        return 1;
                    }
                }
            }
            break;

        default:
            break;
        }

    }

    return 0;
}

void checkCastle(Board* bo)
{
    if (bo->castl[0] == 1 || bo->castl[1] == 1)
    {
        if (getColor(bo, "e1") != 'b' || getPiece(bo, "e1") != 'R')
        {
            bo->castl[0] = 0;
            bo->castl[1] = 0;
        }
        else
        {
            if (getColor(bo, "a1") != 'b' || getPiece(bo, "a1") != 'T')
            {
                bo->castl[0] = 0;
            }
            else if (getColor(bo, "h1") != 'b' || getPiece(bo, "a1") != 'T')
            {
                bo->castl[1] = 0;
            }
        }
    }

    if (bo->castl[1] == 1 || bo->castl[2] == 1)
    {
        if (getColor(bo, "e8") != 'n' || getPiece(bo, "e8") != 'R')
        {
            bo->castl[2] = 0;
            bo->castl[3] = 0;
        }
        else
        {
            if (getColor(bo, "a8") != 'n' || getPiece(bo, "a8") != 'T')
            {
                bo->castl[2] = 0;
            }
            else if (getColor(bo, "h8") != 'n' || getPiece(bo, "h8") != 'T')
            {
                bo->castl[3] = 0;
            }
        }
    }
}

int isSpot(Board* bo, char pos[3], char color)
{
    for (int i = 0; i < 64; i++)
    {
        if (bo->panel[i][1] == color)
        {
            char move[5] = { getColumnId(i), getRowId(i) + '0', getColumn(pos), getRow(pos) + '0','\0' };
            if (bo->panel[i][0] != 'R' && isMove(bo, move, 1)) return 1;
        }
    }

    return 0;
}

void isPromote(Board* bo)
{
    for (size_t i = 0; i < 8; i++)
    {
        // Peon filas 1 y 8
        if (bo->panel[i][0] == 'P' && bo->panel[i][1] == 'n') bo->panel[i][0] = 'D';
        if (bo->panel[63 - i][0] == 'P' && bo->panel[63 - i][1] == 'b') bo->panel[63 - i][0] = 'D';

        // Peon al paso

        if (bo->panel[i + 16][0] == 'W') bo->panel[i + 16][0] = ' ';
        else if (bo->panel[i + 16][0] == ' ' && bo->panel[i + 16][1] == 'b') {
            bo->panel[i + 16][1] = ' ';
        }

        if (bo->panel[47 - i][0] == 'W') bo->panel[47 - i][0] = ' ';
        else if (bo->panel[47 - i][0] == ' ' && bo->panel[47 - i][1] == 'n') {
            bo->panel[47 - i][1] = ' ';
        }

    }

}

int isNailed(Board* bo, char move[5]) {
    Board aux;
    char nStatus[80], kingPos[3];
    savePanel(bo, nStatus);
    loadPanel(&aux, nStatus);
    char a[2] = { move[0],move[1] };
    char* token = strtok(nStatus, "|");


    movePiece(&aux, move);
    if (getColor(bo, a) == 'n') token = strtok(NULL, "|");
    if (move[0] == token[0] && move[1] == token[1])
    {
        kingPos[0] = move[2];
        kingPos[1] = move[3];
        kingPos[2] = '\0';
    }
    else
    {
        kingPos[0] = token[0];
        kingPos[1] = token[1];
        kingPos[2] = '\0';
    }

    if (isSpot(&aux, kingPos, (getColor(bo, a) == 'b') ? 'n' : 'b')) return 1;
    else return 0;
}

int isCheck(Board* bo, char player) {
    char nStatus[80];
    savePanel(bo, nStatus);
    char* token = strtok(nStatus, "|");
    if (player != 'n') token = strtok(NULL, "|");
    char kingPos[2] = { token[0], token[1] };
    char kingAux[2] = { token[0] - 1, token[1] - 1 };

    if (isSpot(bo, kingPos, player)) {

        for (size_t i = 0; i < 3; i++)
        {
            for (size_t j = 0; j < 3; j++)
            {
                char move[4] = { kingPos[0], kingPos[1], kingAux[0], kingAux[1] };
                if (isMove(bo, move, 0)) {
                    return 1;
                }
                kingAux[0] = kingAux[0] + 1;
            }
            kingAux[1] = kingAux[1] + 1;
            kingAux[0] = kingPos[0] - 1;
        }
        return 2;
    }
    else return 0;
}