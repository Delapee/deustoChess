#if !defined(CHESS)
#define CHESS

typedef struct board
{   
    char panel[64][3];
    int turn;
    int castl[4];
}board;

// Metodos tablero
void prepareBoard(board* bo);
void loadPanel(board *bo, char status[80], int i);              // Carga un estado dentro del tablero
void loadPiece(board *bo, char status[40], char player);
void loadStatus(board *bo, char status[80]);                    // Carga un estado al historial de estados
void printBoard(board *bo, int player);                         // Imprime el tablero teniendo en cuenta el jugador
int checkWin(char status[76]);                                  // Devuelve 0 - Nada | 1 - Jaque | 2 - Mate

// Utilidades
int getPos(char move[3]);                   // Recibe una casilla y devuelve el indice 
char getColumn(char move[3]);               // Devuelve la columna
int getRow(char move[3]);                   // Devuelve la fila
char getPiece(board *bo, char move[3]);     // Devuelve la pieza
char getColor(board *bo, char move[3]);     // Devuelve el color

// Movimento
void move(board *bo, char move[5]);                      // Mueve una pieza de a -> b
int isMove(board* bo, char move[5]);       // Comprueba que es posible mover de a -> b

#endif // CHESS