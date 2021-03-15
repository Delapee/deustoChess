#if !defined(CHESS)
#define CHESS

typedef struct Board
{   
    char panel[64][3];
    int turn;
    int castl[4];
}Board;

// Metodos tablero
void test(void);
void prepareBoard(Board * bo);
void loadPanel(Board *bo, char status[80], int i);              // Carga un estado dentro del tablero
void loadPiece(Board *bo, char status[40], char player);
void loadStatus(Board *bo, char status[80]);                    // Carga un estado al historial de estados
void printBoard(Board *bo, int player);                         // Imprime el tablero teniendo en cuenta el jugador
int checkWin(char status[76]);                                  // Devuelve 0 - Nada | 1 - Jaque | 2 - Mate
void checkCastle(Board *bo);

// Utilidades
int getPos(char move[3]);                   // Recibe una casilla y devuelve el indice 
char getColumn(char move[3]);               // Devuelve la columna
int getRow(char move[3]);                   // Devuelve la fila
char getPiece(Board *bo, char move[3]);     // Devuelve la pieza
char getColor(Board *bo, char move[3]);     // Devuelve el color

// Movimento
void movePiece(Board *bo, char move[5]);         // Mueve una pieza de a -> b
int isMove(Board *bo, char move[5]);        // Comprueba que es posible mover de a -> b

#endif // CHESS